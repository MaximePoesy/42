#!/bin/sh
# init-vault.sh — one-shot Vault initialization for ft_transcendance
# Runs every restart; only vault operator init is skipped if already initialized.
set -e

VAULT_ADDR="${VAULT_ADDR:-http://ft_vault:8200}"
VAULT_INIT_DIR="${VAULT_INIT_DIR:-/vault/init}"
VAULT_SECRETS_DIR="${VAULT_SECRETS_DIR:-/vault/secrets}"
VAULT_TOKEN_FILE="${VAULT_SECRETS_DIR}/.root-token"
VAULT_KEY_FILE="${VAULT_SECRETS_DIR}/.unseal-key"
INIT_MARKER="${VAULT_SECRETS_DIR}/.initialized"

export VAULT_ADDR

log()  { echo "[vault-init] $*"; }
fail() { echo "[vault-init] ERROR: $*" >&2; exit 1; }

# ---------------------------------------------------------------------------
# 1. Wait for Vault to be reachable (exit 0 = unsealed, 2 = sealed, 1 = error)
# ---------------------------------------------------------------------------
log "Waiting for Vault at $VAULT_ADDR..."
i=0
while true; do
  if vault status > /dev/null 2>&1; then
    code=0; break
  else
    code=$?
    [ "$code" -eq 2 ] && break
  fi
  i=$((i + 1))
  [ "$i" -ge 30 ] && fail "Vault did not become reachable after 30 attempts"
  sleep 2
done
log "Vault is reachable (exit code $code)"

mkdir -p "$VAULT_INIT_DIR" "$VAULT_SECRETS_DIR"

# ---------------------------------------------------------------------------
# 2. Initialize (only once — skipped if marker exists)
# ---------------------------------------------------------------------------
if [ ! -f "$INIT_MARKER" ]; then
  log "Initializing Vault..."
  INIT_OUTPUT=$(vault operator init -key-shares=1 -key-threshold=1 -format=json) \
    || fail "vault operator init failed"

  # Parse with grep + sed — no jq in image
  UNSEAL_KEY=$(printf '%s' "$INIT_OUTPUT" | grep '"unseal_keys_b64"' -A1 | grep -o '"[A-Za-z0-9+/=]*"' | tr -d '"' | head -1)
  ROOT_TOKEN=$(printf '%s' "$INIT_OUTPUT" | grep '"root_token"' | sed 's/.*"root_token" *: *"\([^"]*\)".*/\1/')

  [ -z "$UNSEAL_KEY" ] && fail "Could not parse unseal key from init output:\n$INIT_OUTPUT"
  [ -z "$ROOT_TOKEN" ] && fail "Could not parse root token from init output:\n$INIT_OUTPUT"

  printf '%s' "$UNSEAL_KEY" > "$VAULT_KEY_FILE"
  printf '%s' "$ROOT_TOKEN" > "$VAULT_TOKEN_FILE"
  chmod 600 "$VAULT_KEY_FILE" "$VAULT_TOKEN_FILE"
  log "Vault initialized. Credentials stored in $VAULT_SECRETS_DIR"
else
  log "Vault already initialized (marker exists)"
fi

# ---------------------------------------------------------------------------
# 3. Unseal if sealed
# ---------------------------------------------------------------------------
if vault status > /dev/null 2>&1; then
  seal_code=0
else
  seal_code=$?
fi
if [ "$seal_code" -eq 2 ]; then
  log "Vault is sealed. Unsealing..."
  [ ! -f "$VAULT_KEY_FILE" ] && fail "Unseal key not found at $VAULT_KEY_FILE"
  UNSEAL_KEY=$(cat "$VAULT_KEY_FILE")
  vault operator unseal "$UNSEAL_KEY" > /dev/null || fail "vault operator unseal failed"
  log "Vault unsealed"
elif [ "$seal_code" -eq 0 ]; then
  log "Vault is already unsealed"
else
  fail "vault status returned unexpected exit code $seal_code"
fi

# ---------------------------------------------------------------------------
# 4. Authenticate with root token
# ---------------------------------------------------------------------------
[ ! -f "$VAULT_TOKEN_FILE" ] && fail "Root token not found at $VAULT_TOKEN_FILE"
export VAULT_TOKEN
VAULT_TOKEN=$(cat "$VAULT_TOKEN_FILE")
log "Authenticated as root"

# ---------------------------------------------------------------------------
# 5. Enable KV v2 secrets engine (idempotent)
# ---------------------------------------------------------------------------
if vault secrets list -format=json | grep -q '"secret/"'; then
  log "KV secrets engine already enabled at secret/"
else
  vault secrets enable -path=secret kv-v2 > /dev/null || fail "Failed to enable kv-v2"
  log "KV v2 secrets engine enabled at secret/"
fi

# ---------------------------------------------------------------------------
# 6. Enable AppRole auth (idempotent)
# ---------------------------------------------------------------------------
if vault auth list -format=json | grep -q '"approle/"'; then
  log "AppRole auth already enabled"
else
  vault auth enable approle > /dev/null || fail "Failed to enable approle"
  log "AppRole auth enabled"
fi

# ---------------------------------------------------------------------------
# 7. Write policies
# ---------------------------------------------------------------------------
vault policy write policy-back - > /dev/null <<'POLICY'
path "secret/data/ft_transcendance/back" { capabilities = ["read"] }
path "secret/metadata/ft_transcendance/back" { capabilities = ["read", "list"] }
POLICY
log "Policy 'policy-back' written"

vault policy write policy-ai - > /dev/null <<'POLICY'
path "secret/data/ft_transcendance/ai" { capabilities = ["read"] }
path "secret/metadata/ft_transcendance/ai" { capabilities = ["read", "list"] }
POLICY
log "Policy 'policy-ai' written"

# ---------------------------------------------------------------------------
# 8. Write secrets — driven by BACK__* and AI__* environment variables.
#    To add a new secret: add BACK__<key>=<value> or AI__<key>=<value> to
#    the vault-init environment in docker-compose.yml. No changes needed here.
# ---------------------------------------------------------------------------
BACK_ARGS=$(printenv | grep '^BACK__' | sed 's/^BACK__//')
AI_ARGS=$(printenv   | grep '^AI__'   | sed 's/^AI__//')

[ -z "$BACK_ARGS" ] && fail "No BACK__* env vars found — nothing to write for back service"
[ -z "$AI_ARGS"   ] && fail "No AI__* env vars found — nothing to write for ai-engine service"

vault kv put secret/ft_transcendance/back $BACK_ARGS \
  > /dev/null || fail "Failed to write back secrets"
log "Secrets written: secret/ft_transcendance/back"

vault kv put secret/ft_transcendance/ai $AI_ARGS \
  > /dev/null || fail "Failed to write ai secrets"
log "Secrets written: secret/ft_transcendance/ai"

# ---------------------------------------------------------------------------
# 9. Create AppRoles and store credentials
# ---------------------------------------------------------------------------
vault write auth/approle/role/back \
  token_ttl=1h token_max_ttl=4h \
  token_policies=policy-back \
  token_no_default_policy=true > /dev/null \
  || fail "Failed to create AppRole 'back'"

vault write auth/approle/role/ai \
  token_ttl=1h token_max_ttl=4h \
  token_policies=policy-ai \
  token_no_default_policy=true > /dev/null \
  || fail "Failed to create AppRole 'ai'"

BACK_ROLE_ID=$(vault read -field=role_id auth/approle/role/back/role-id) \
  || fail "Failed to read back role-id"
BACK_SECRET_ID=$(vault write -f -field=secret_id auth/approle/role/back/secret-id) \
  || fail "Failed to generate back secret-id"

AI_ROLE_ID=$(vault read -field=role_id auth/approle/role/ai/role-id) \
  || fail "Failed to read ai role-id"
AI_SECRET_ID=$(vault write -f -field=secret_id auth/approle/role/ai/secret-id) \
  || fail "Failed to generate ai secret-id"

printf '%s' "$BACK_ROLE_ID"   > "$VAULT_INIT_DIR/back-role-id"
printf '%s' "$BACK_SECRET_ID" > "$VAULT_INIT_DIR/back-secret-id"
printf '%s' "$AI_ROLE_ID"     > "$VAULT_INIT_DIR/ai-role-id"
printf '%s' "$AI_SECRET_ID"   > "$VAULT_INIT_DIR/ai-secret-id"
chmod 600 "$VAULT_INIT_DIR"/back-* "$VAULT_INIT_DIR"/ai-*
log "AppRole credentials written to $VAULT_INIT_DIR"

# ---------------------------------------------------------------------------
# 10. Smoke test — use throwaway secret_ids, never consume the service ones
# ---------------------------------------------------------------------------
BACK_KEY=$(printenv | grep '^BACK__' | head -1 | sed 's/^BACK__//' | sed 's/=.*//')
AI_KEY=$(printenv   | grep '^AI__'   | head -1 | sed 's/^AI__//'   | sed 's/=.*//')

log "Smoke test: back service login..."
BACK_TEST_SECRET_ID=$(vault write -f -field=secret_id auth/approle/role/back/secret-id) \
  || fail "Failed to generate throwaway back secret-id for smoke test"
BACK_TOKEN=$(vault write -field=token auth/approle/login \
  role_id="$BACK_ROLE_ID" secret_id="$BACK_TEST_SECRET_ID") \
  || fail "back AppRole login failed"

VAULT_TOKEN="$BACK_TOKEN" vault kv get secret/ft_transcendance/back > /dev/null \
  || fail "back service cannot read its secrets"
log "back service can read its secrets (spot-checked key: $BACK_KEY)"

log "Smoke test: ai-engine service login..."
AI_TEST_SECRET_ID=$(vault write -f -field=secret_id auth/approle/role/ai/secret-id) \
  || fail "Failed to generate throwaway ai secret-id for smoke test"
AI_TOKEN=$(vault write -field=token auth/approle/login \
  role_id="$AI_ROLE_ID" secret_id="$AI_TEST_SECRET_ID") \
  || fail "ai AppRole login failed"

VAULT_TOKEN="$AI_TOKEN" vault kv get secret/ft_transcendance/ai > /dev/null \
  || fail "ai-engine service cannot read its secrets"
log "ai-engine service can read its secrets (spot-checked key: $AI_KEY)"

log "Smoke test: isolation check (back must NOT read ai secrets)..."
if VAULT_TOKEN="$BACK_TOKEN" vault kv get secret/ft_transcendance/ai > /dev/null 2>&1; then
  echo "[vault-init] WARN: back service can read ai secrets — check policies" >&2
else
  log "Isolation OK: back cannot read ai secrets"
fi

log "Vault initialization complete"
touch "$INIT_MARKER"
