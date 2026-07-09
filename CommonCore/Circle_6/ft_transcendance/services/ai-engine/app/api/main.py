import json
import datetime
from fastapi import FastAPI, HTTPException, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import StreamingResponse
from pydantic import BaseModel, Field
from slowapi import Limiter, _rate_limit_exceeded_handler
from slowapi.util import get_remote_address
from slowapi.errors import RateLimitExceeded

from app.parsers.hl7_parser import parse_hl7_to_fhir, HL7ParsingError
from app.services.ollama_client import ollama_client
from app.services.vector_store import vector_store
from app.services.vault_config import load_vault_secrets

# Load secrets from HashiCorp Vault
load_vault_secrets()

# Per-IP rate limiter (used by the streaming LLM endpoints).
# Behind the WAF, remote_address is always the nginx container IP, which would
# make the limit global across all users. nginx sets X-Real-IP to the actual
# client address, so key on that and only fall back to the socket address.
def real_client_ip(request: Request) -> str:
    return request.headers.get("x-real-ip") or get_remote_address(request)

limiter = Limiter(key_func=real_client_ip)

# Initialize FastAPI application with metadata
app = FastAPI(
    title="AI Engine API",
    description="Microservice responsible for parsing medical data and orchestrating AI workflows.",
    version="1.0.0"
)
app.state.limiter = limiter
app.add_exception_handler(RateLimitExceeded, _rate_limit_exceeded_handler)


def sse_pack(event: str, data: dict) -> str:
    """Encode a payload as one Server-Sent Event frame."""
    return f"event: {event}\ndata: {json.dumps(data)}\n\n"


def join_context(documents: list[str]) -> str:
    """Join retrieved documents, dropping exact duplicates while preserving order.

    The vector store already upserts by content hash, but a near-empty corpus can
    still surface the same patient summary more than once in the top-k window. A
    context that repeats the same record nudges small models into listing loops,
    so we collapse identical chunks before building the prompt.
    """
    seen: set[str] = set()
    unique = [d for d in documents if not (d in seen or seen.add(d))]
    return "\n".join(unique)

# CORS: browsers only ever reach this service through the WAF TLS ingress,
# so that is the only origin allowed. Server-to-server calls are unaffected.
app.add_middleware(
    CORSMiddleware,
    allow_origins=["https://localhost:8443"],
    allow_credentials=False,
    allow_methods=["POST", "GET", "OPTIONS"],
    allow_headers=["*"],
)

# Request schemas — Pydantic validates every payload before the handler runs.
# Lengths are upper bounds; the parser is the source of truth for HL7 correctness.
HL7_MAX = 64 * 1024     # 64 KiB — a generous HL7 v2 message is a few KB at most
QUESTION_MAX = 2_000    # one paragraph of natural language
MESSAGE_MAX = 4_000     # chat input
HISTORY_MAX = 50        # number of past turns we accept

class HL7Input(BaseModel):
    """Schema for incoming HL7 parsing requests."""
    hl7: str = Field(..., min_length=1, max_length=HL7_MAX, description="Raw HL7 v2 string content")

class ChatTurn(BaseModel):
    """One message in a chat history."""
    role: str = Field(..., min_length=1, max_length=32)
    content: str = Field(..., min_length=1, max_length=MESSAGE_MAX)

class ChatInput(BaseModel):
    """Schema for AI chat requests."""
    message: str = Field(..., min_length=1, max_length=MESSAGE_MAX, description="User message for the AI")
    history: list[ChatTurn] = Field(default_factory=list, max_length=HISTORY_MAX, description="Chat history")

class RagInput(BaseModel):
    """Schema for RAG-based queries."""
    question: str = Field(..., min_length=1, max_length=QUESTION_MAX, description="Question about the medical records")

@app.post("/ai/convert", summary="Parse HL7 to FHIR", response_description="A FHIR R4 Bundle in JSON format")
def parse_hl7(payload: HL7Input):
    """
    Parses an incoming raw HL7 v2 message and converts it into a structured FHIR R4 Bundle.
    """
    try:
        fhir_bundle = parse_hl7_to_fhir(payload.hl7)

        # Create a human-readable summary for better RAG retrieval
        # Small models like SmolLM2 handle natural language better than JSON/HL7
        summary = "Medical Record Data: "
        for entry in fhir_bundle.entry:
            resource_type = entry.resource.get_resource_type()
            if resource_type == "Patient":
                p = entry.resource
                name_str = "Unknown"
                if p.name and len(p.name) > 0:
                    first_name = " ".join(p.name[0].given) if p.name[0].given else ""
                    last_name = p.name[0].family if p.name[0].family else ""
                    if first_name or last_name:
                        name_str = f"{first_name} {last_name}".strip()

                gender_str = p.gender if p.gender else "Unknown"
                dob_str = p.birthDate if p.birthDate else "Unknown"
                summary += f"Patient Name: {name_str}. Gender: {gender_str}. Birth Date: {dob_str}. "

            if resource_type == "Observation":
                o = entry.resource
                display_str = "Unknown Test"
                if o.code and o.code.coding and len(o.code.coding) > 0:
                    display_str = o.code.coding[0].display or o.code.coding[0].code or "Unknown Test"

                val_str = "N/A"
                if hasattr(o, "valueQuantity") and o.valueQuantity:
                    # value is stored as a Decimal built from a binary float, so a
                    # clean "4.8" can serialize as "4.79999...". Reformat via float
                    # + :g so the indexed text stays human-readable for the LLM.
                    num = f"{float(o.valueQuantity.value):g}"
                    val_str = f"{num} {o.valueQuantity.unit or ''}".strip()
                elif hasattr(o, "valueString") and o.valueString:
                    val_str = o.valueString

                summary += f"Laboratory Result for {display_str}: {val_str}. "

        # Index the summary for vector search, and store the raw data in metadata
        # to avoid exceeding the embedding model's context length (all-minilm has a small context window)
        vector_store.add_document(
            text=summary,
            metadata={"type": "hl7_summary", "raw": payload.hl7}
        )

        # Return FHIR bundle as a pretty-printed JSON string under the "fhir" key.
        # The default handler converts date/datetime objects to ISO 8601 strings
        # (e.g. date(1980,1,1) → "1980-01-01"), which is the correct FHIR date format.
        return {"fhir": json.dumps(
            fhir_bundle.model_dump(exclude_none=True),
            indent=2,
            default=lambda o: o.isoformat() if isinstance(o, (datetime.date, datetime.datetime)) else str(o)
        )}

    except HL7ParsingError as e:
        raise HTTPException(status_code=400, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Internal AI Engine error: {str(e)}")

@app.post("/ai/chat", summary="Direct AI Chat")
def ai_chat(payload: ChatInput):
    """Interact directly with SmolLM2."""
    try:
        system_msg = {
            "role": "system",
            "content": "You are a professional medical interoperability (HL7/FHIR) assistant. Be concise. Never invent clinical facts. IMPORTANT: Always reply in the exact same language as the user's prompt (English, French, or Spanish)."
        }
        history_dicts = [turn.model_dump() for turn in payload.history]
        messages = [system_msg] + history_dicts + [{"role": "user", "content": payload.message}]
        response = ollama_client.chat(messages)
        return {"response": response}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/ai/rag", summary="RAG-based Medical Query")
def ai_rag(payload: RagInput):
    """Query the AI using medical records as context."""
    try:
        # 1. Retrieve relevant context
        results = vector_store.query(payload.question)

        # Check if we actually have documents
        if not results or not results['documents'] or not results['documents'][0]:
            # No context found, fall back to general chat or a polite refusal
            response = ollama_client.chat([{"role": "user", "content": payload.question}])
            return {
                "response": response,
                "sources": [],
                "note": "No specific medical records found in context."
            }

        context = join_context(results['documents'][0])

        # 2. Build augmented prompt
        # Use the "system" role to enforce rules strongly
        system_content = f"""You are a medical records assistant. The CONTEXT below contains patient records.
Find the patient named in the question and list everything the CONTEXT says about them: identity (name, gender, birth date) and every laboratory result with its exact value and unit. Quote values exactly; do not rename tests or invent anything.
Refuse ONLY if that patient's name does not appear anywhere in the CONTEXT — in that case reply exactly: 'I do not have this information in the records.' If the name is present, you must answer, never refuse.
Reply in the same language as the question.

CONTEXT:
{context}"""
        messages = [
            {"role": "system", "content": system_content},
            {"role": "user", "content": payload.question}
        ]

        # 3. Generate response
        response = ollama_client.chat(messages)

        return {
            "response": response,
            "sources": results['metadatas'][0]
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/ai/llm/stream", summary="Direct LLM stream (no retrieval)")
@limiter.limit("10/minute")
async def ai_llm_stream(payload: RagInput, request: Request):
    """Pure LLM endpoint: no vector retrieval, no record context.

    Use this for general questions ("How does HL7 map to FHIR?", "What is a
    FHIR bundle?") where the answer should come from the model's own knowledge.
    Records-grounded answers go through /ai/rag/stream.
    """
    def event_stream():
        try:
            messages = [
                {
                    "role": "system",
                    "content": (
                        "You are a helpful assistant. Answer concisely. When a "
                        "question concerns medical interoperability standards "
                        "(HL7 v2, FHIR R4, mapping rules), provide accurate "
                        "technical information. Do not invent facts about a "
                        "specific patient — those questions must use the "
                        "Records mode. IMPORTANT: Always reply in the exact "
                        "same language as the user's prompt (English, French, "
                        "or Spanish)."
                    ),
                },
                {"role": "user", "content": payload.question},
            ]
            for token in ollama_client.chat_stream(messages):
                yield sse_pack("token", {"content": token})
            yield sse_pack("done", {})
        except ConnectionError:
            yield sse_pack("error", {"code": "LLM_UNAVAILABLE", "message": "AI service is down"})
        except Exception as e:
            yield sse_pack("error", {"code": "INTERNAL", "message": str(e)})

    return StreamingResponse(
        event_stream(),
        media_type="text/event-stream",
        headers={"Cache-Control": "no-cache", "X-Accel-Buffering": "no"},
    )


@app.post("/ai/rag/stream")
@limiter.limit("10/minute")
async def ai_rag_stream(payload: RagInput, request: Request):
    def event_stream():
        try:
            results = vector_store.query(payload.question)

            if not results or not results['documents'] or not results['documents'][0]:
                # No context — fall back to plain chat, signal it
                yield sse_pack("sources", {"sources": [], "note": "No medical records found"})
                messages = [{"role": "user", "content": payload.question}]
            else:
                yield sse_pack("sources", {"sources": results['metadatas'][0]})
                context = join_context(results['documents'][0])
                
                system_content = f"""You are a medical records assistant. The CONTEXT below contains patient records.
Find the patient named in the question and list everything the CONTEXT says about them: identity (name, gender, birth date) and every laboratory result with its exact value and unit. Quote values exactly; do not rename tests or invent anything.
Refuse ONLY if that patient's name does not appear anywhere in the CONTEXT — in that case reply exactly: 'I do not have this information in the records.' If the name is present, you must answer, never refuse.
Reply in the same language as the question.

CONTEXT:
{context}"""
                messages = [
                    {"role": "system", "content": system_content},
                    {"role": "user", "content": payload.question}
                ]

            for token in ollama_client.chat_stream(messages):
                yield sse_pack("token", {"content": token})
            yield sse_pack("done", {})
        except ConnectionError:
            yield sse_pack("error", {"code": "LLM_UNAVAILABLE", "message": "AI service is down"})
        except Exception as e:
            yield sse_pack("error", {"code": "INTERNAL", "message": str(e)})

    return StreamingResponse(
        event_stream(),
        media_type="text/event-stream",
        headers={"Cache-Control": "no-cache", "X-Accel-Buffering": "no"},
    )
