# Vault configuration for production mode with file backend
# Reference: https://developer.hashicorp.com/vault/docs/configuration

storage "file" {
  path = "/vault/file"
}

listener "tcp" {
  address       = "0.0.0.0:8200"
  tls_disable   = 1  # TLS handled by WAF/reverse proxy in production
}

# mlock requires kernel support that is not available on every Docker host
# (fails with "Failed to lock memory: cannot allocate memory" on Arch and
# some CI runners). Disabling it is the documented recommendation for
# containerized Vault deployments backed by a file storage.
disable_mlock = true

ui = true
