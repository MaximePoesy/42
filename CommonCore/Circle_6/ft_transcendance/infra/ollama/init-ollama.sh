#!/bin/sh
# Pull the models required by the AI engine.
#
# The Ollama CLI is a remote API client: with OLLAMA_HOST pointing at the
# running daemon, every `ollama pull` triggers the daemon to download into
# its own volume. Pulls are idempotent — subsequent runs are no-ops.
set -eu

OLLAMA_HOST="${OLLAMA_HOST:-http://ollama:11434}"
export OLLAMA_HOST

MODELS="${OLLAMA_MODELS:-smollm2:135m all-minilm}"

echo "ollama-init: waiting for daemon at $OLLAMA_HOST..."
# /api/tags returns 200 once the daemon is ready to serve.
until ollama list >/dev/null 2>&1; do
  sleep 2
done
echo "ollama-init: daemon is ready"

for model in $MODELS; do
  echo "ollama-init: pulling $model..."
  ollama pull "$model"
done

echo "ollama-init: all models present"
