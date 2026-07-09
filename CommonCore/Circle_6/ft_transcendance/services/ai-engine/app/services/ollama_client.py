import os
import ollama
from typing import List, Dict, Any, Iterator

# Generation guardrails. Small models (smollm2:135m) degenerate into
# repetition loops ("1. patient name 2. patient name 3. ...") under greedy
# decoding. These options break the cycle and cap the worst case:
#   temperature     a touch of noise so decoding is not purely deterministic
#   repeat_penalty  penalises re-emitting the same tokens (default 1.1 is too weak here)
#   num_predict     hard ceiling on generated tokens; without it Ollama runs
#                   until the context is full, so a loop can spew endlessly
CHAT_OPTIONS = {
    "temperature": 0.2,
    "repeat_penalty": 1.3,
    "num_predict": 512,
}


class OllamaClient:
    def __init__(self, host: str = None):
        if host is None:
            host = os.getenv("OLLAMA_HOST", "http://ollama:11434")
        self.client = ollama.Client(host=host)
        self.model = os.getenv("LLM_MODEL", "smollm2:135m")

    def chat(self, messages: List[Dict[str, str]]) -> str:
        """Simple chat completion."""
        response = self.client.chat(model=self.model, messages=messages, options=CHAT_OPTIONS)
        return response['message']['content']

    def chat_stream(self, messages: List[Dict[str, str]]) -> Iterator[str]:
        """Yield tokens as they are produced by Ollama."""
        stream = self.client.chat(model=self.model, messages=messages, stream=True, options=CHAT_OPTIONS)
        for chunk in stream:
            if chunk.get('message', {}).get('content'):
                yield chunk['message']['content']

    def generate_embeddings(self, text: str) -> List[float]:
        """Generate embeddings using all-minilm."""
        response = self.client.embeddings(model="all-minilm", prompt=text)
        return response['embedding']

ollama_client = OllamaClient()
