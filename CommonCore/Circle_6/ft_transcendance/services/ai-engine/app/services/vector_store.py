import hashlib
from typing import Any, Dict, List

import chromadb
from chromadb.api.types import Documents, EmbeddingFunction, Embeddings

from .ollama_client import ollama_client


class OllamaEmbeddingFunction(EmbeddingFunction):
    """Route every Chroma embedding call through our Ollama daemon.

    Keeps a single AI provider (Ollama) for both inference and embeddings,
    matches the model documented in the README (all-minilm via Ollama), and
    makes the data path easy to reason about during evaluation.
    """

    # Chroma >=0.5 persists this string in the collection metadata so it can
    # detect mismatches between the function used at indexing time and the
    # one used at query time. Without an explicit name, Chroma stores
    # "NotImplemented" and every reopen raises a conflict error.
    @staticmethod
    def name() -> str:
        return "ollama-all-minilm"

    def __call__(self, input: Documents) -> Embeddings:
        return [ollama_client.generate_embeddings(text) for text in input]


class VectorStore:
    def __init__(self, path: str = "/app/db/chroma"):
        self.client = chromadb.PersistentClient(path=path)
        self.collection = self.client.get_or_create_collection(
            name="medical_records",
            embedding_function=OllamaEmbeddingFunction(),
        )

    def add_document(self, text: str, metadata: Dict[str, Any]):
        """Index a document. Embedding is delegated to Ollama via the
        collection's embedding function.

        The id is derived deterministically from the source content (the raw
        HL7 message when available, otherwise the summary text). Re-posting the
        same message therefore upserts the same row instead of piling up
        identical duplicates that would otherwise crowd out every other record
        from the top-k retrieval window.
        """
        dedup_key = metadata.get("raw") or text
        doc_id = hashlib.sha256(dedup_key.encode("utf-8")).hexdigest()
        self.collection.upsert(
            documents=[text],
            metadatas=[metadata],
            ids=[doc_id],
        )

    def query(self, query_text: str, n_results: int = 3) -> List[Dict[str, Any]]:
        """Vector-search the collection. Same embedder is used on the query so
        retrieval is symmetric with indexing."""
        return self.collection.query(
            query_texts=[query_text],
            n_results=n_results,
        )


vector_store = VectorStore()
