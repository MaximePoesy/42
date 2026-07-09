import os

import hvac


def load_vault_secrets():
    vault_url = os.getenv("VAULT_ADDR", "http://ft_vault:8200")
    role_id_file = os.getenv("VAULT_ROLE_ID_FILE")
    secret_id_file = os.getenv("VAULT_SECRET_ID_FILE")

    if not role_id_file or not secret_id_file:
        print("⚠️ VAULT_ROLE_ID_FILE or VAULT_SECRET_ID_FILE not set")
        return

    try:
        # Read AppRole credentials from files (set by vault-init container)
        with open(role_id_file, "r") as f:
            role_id = f.read().strip()
        with open(secret_id_file, "r") as f:
            secret_id = f.read().strip()

        if not role_id or not secret_id:
            print("⚠️ AppRole credentials are empty")
            return

        print(f"🔐 Authenticating to Vault at {vault_url} using AppRole...")

        # Create an unauthenticated client
        client = hvac.Client(url=vault_url)

        # Authenticate using AppRole
        auth_response = client.auth.approle.login(role_id=role_id, secret_id=secret_id)

        token = auth_response["auth"]["client_token"]
        print("✅ AppRole authentication successful")

        # Create a new authenticated client
        authenticated_client = hvac.Client(url=vault_url, token=token)

        # Read secrets from the ai-engine service path
        read_response = authenticated_client.secrets.kv.v2.read_secret_version(
            path="ft_transcendance/ai", mount_point="secret"
        )
        secrets = read_response["data"]["data"]

        # Populate environment variables
        for key, value in secrets.items():
            env_var_name = f"VAULT_{key.upper()}"
            os.environ[env_var_name] = str(value)
            # Also set without VAULT_ prefix for convenience
            os.environ[key.upper()] = str(value)

        print("✅ AI Engine: Secrets loaded from Vault (AppRole authenticated)")

    except FileNotFoundError as e:
        print(f"⚠️ AI Engine: Could not read AppRole credentials from files: {e}")
    except Exception as e:
        print(f"⚠️ AI Engine: Could not load secrets from Vault: {e}")


# Convenience mapping for expected environment variable names
# (in case service code expects non-prefixed names like OLLAMA_HOST instead of VAULT_OLLAMA_HOST)
def get_vault_secret(key: str, default: str = "") -> str:
    """Get a secret from environment, with or without VAULT_ prefix."""
    return os.environ.get(f"VAULT_{key.upper()}", os.environ.get(key.upper(), default))
