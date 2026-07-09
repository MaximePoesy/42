# Cybersecurity: WAF & HashiCorp Vault

This document describes how the **Web Application Firewall (WAF)** and **HashiCorp Vault** are deployed in `ft_transcendance`. Together they cover the _"WAF/ModSecurity (hardened) + HashiCorp Vault for secrets"_ major module of the subject.

---

## 1. HashiCorp Vault (secrets management)

### Goal

Application code never sees credentials. Instead, every service authenticates to Vault at boot using a short-lived AppRole identity, reads its own secrets from a service-scoped path, and only then validates its environment. Root credentials never leave a single one-shot container.

### Configuration

- **Image:** `hashicorp/vault:latest` (container `ft_vault`).
- **Mode:** **production / file backend** — _not_ dev mode. The storage backend is a file volume mounted at `/vault/file`, and Vault is started with an explicit `-config` flag (see `infra/vault/config.hcl`).
- **Initialisation:** done by a separate one-shot container, `ft_vault_init`, that runs `infra/vault/init-vault.sh`. The script:
  1. Initialises and unseals Vault (storing the unseal keys + root token in `vault_secrets`, a volume **never mounted** by app containers).
  2. Enables the KV v2 secrets engine at `secret/`.
  3. Writes per-service secrets under `secret/ft_transcendance/back` and `secret/ft_transcendance/ai`.
  4. Enables the AppRole auth method and creates one role per service.
  5. Drops each role's `role_id` + `secret_id` into a dedicated read-only volume (`vault_init`) that is bind-mounted into the corresponding service container.
- **Listener:** plain HTTP on the internal Docker network (TLS is terminated at the WAF). No port published to the host.

### Service authentication flow

```
docker compose up
   │
   ├── ft_vault starts          (file backend, sealed -> unsealed by init)
   ├── ft_vault_init runs       (writes role-id / secret-id files)
   └── ft_back / ft_ai-engine start
            │
            └── read role-id + secret-id from /vault/init (read-only)
                │
                └── POST /v1/auth/approle/login → short-lived token
                       │
                       └── GET /v1/secret/data/ft_transcendance/<role>
                              │
                              └── populate process.env / os.environ
```

- Back-end code: `back/src/vaultConfig.ts` (uses `node-vault`).
- AI engine code: `services/ai-engine/app/services/vault_config.py` (uses `hvac`).

### Key files / volumes

| Path / volume                            | Purpose                                                           |
| ---------------------------------------- | ----------------------------------------------------------------- |
| `infra/vault/config.hcl`                 | Production file backend + listener configuration.                 |
| `infra/vault/init-vault.sh`              | One-shot bootstrap script run by `ft_vault_init`.                 |
| `vault_data` (volume)                    | Vault file backend — encrypted at rest by Vault itself.           |
| `vault_secrets` (volume)                 | Root token + unseal keys. Mounted **only** by the init container. |
| `vault_init` (volume, read-only in apps) | Per-service `role-id` / `secret-id` files.                        |

### Health checks

`docker exec ft_vault vault status` should report `Initialized: true`, `Sealed: false`, and `Storage Type: file`.

---

## 2. WAF — ModSecurity + OWASP CRS (hardened)

### Goal

The WAF is the **single ingress** of the platform: every browser, script, or external probe must traverse it before reaching the app. It enforces TLS, normalises requests, applies a tuned ModSecurity rule set, and acts as the first rate-limit layer.

### Topology

```
                       ┌──────────┐
       browser ──TLS──▶│  ft_waf  │── http ──▶ front / back / ai-engine
                       └──────────┘
                            ▲
                            └── only host-published port: :8443 (TLS), :8080 (HTTP→HTTPS redirect)
```

In production (`make up`) nothing else is published. The dev stack (`make dev`) additionally exposes Vite (`5173`), Express (`3001`), FastAPI (`8000`), Vault UI (`8201`), Ollama (`11434`), and pgAdmin (`5050`) — **loopback only, for debugging**; they are not the supported entry point.

### Configuration

- **Image:** `owasp/modsecurity-crs:nginx-alpine`.
- **Reverse proxy:** `infra/nginx/default.conf` (mounted into `/etc/nginx/templates/conf.d/`).
- **Custom CRS exclusion:** `infra/waf/REQUEST-900-EXCLUSION-RULES-BEFORE-CRS.conf` (declares the methods we actually use).
- **Engine settings (only overrides vs the image defaults — `MODSEC_RULE_ENGINE=On`, `MODSEC_AUDIT_ENGINE=RelevantOnly`, `MODSEC_AUDIT_LOG=/dev/stdout`, `MODSEC_REQ_BODY_LIMIT=1048576`, `HTTP2=on`, resolver auto-detected from `/etc/resolv.conf` are all already correct out of the box):**

  | Variable                      | Value                                            | Why                                                                                                |
  | ----------------------------- | ------------------------------------------------ | -------------------------------------------------------------------------------------------------- |
  | `BLOCKING_PARANOIA`           | `2`                                              | Above CRS default (1). CRS v4 native name (replaces legacy `PARANOIA`).                            |
  | `DETECTION_PARANOIA`          | `2`                                              | Evaluate at the same level we block on (CRS v4 native name, replaces legacy `EXECUTING_PARANOIA`). |
  | `ANOMALY_INBOUND`             | `10`                                             | Anomaly threshold above which an inbound request is blocked (CRS default: 5).                      |
  | `ANOMALY_OUTBOUND`            | `5`                                              | Same on the response side (CRS default: 4).                                                        |
  | `ALLOWED_METHODS`             | `GET HEAD POST OPTIONS PUT DELETE`               | API uses PUT + DELETE; CRS default would block them.                                               |
  | `ENFORCE_BODYPROC_URLENCODED` | `1`                                              | Force URL-encoded body inspection even when the attacker omits the `Content-Type` header.          |
  | `MODSEC_RESP_BODY_MIMETYPE`   | `text/plain text/html text/xml application/json` | Image default does not include JSON; without this, CRS would silently skip every API response.     |
  | `ACCESSLOG`                   | `/dev/stdout`                                    | Stream nginx access logs to `docker logs ft_waf` for live debugging.                               |
  | `KEEPALIVE_TIMEOUT`           | `30s`                                            | Tighter than the image default (60s).                                                              |

### TLS hardening (Nginx)

The Nginx config (`infra/nginx/default.conf`) is mounted as the image's `default.conf.template` and processed inside the image-generated `http{}` block. That `http{}` block already provides `keepalive_timeout` (via `KEEPALIVE_TIMEOUT`), `http2 on`, and a resolver auto-detected from `/etc/resolv.conf`, so our file does **not** redeclare any of them — that was the source of an earlier `keepalive_timeout duplicate` boot failure.

- `:8080` is a dedicated server block that returns **`301 https://$host:8443$request_uri`** for everything except `/health` (kept on HTTP for Docker/external probes that don't trust the self-signed cert). There is no application content served on plain HTTP.
- `:8443` enables:
  - `ssl_protocols TLSv1.2 TLSv1.3` (older versions disabled).
  - A modern ECDHE/CHACHA20-only cipher list, with `ssl_prefer_server_ciphers off` (TLS 1.3 negotiation).
  - Shared session cache (`shared:SSL:10m`), 1 h timeout, session tickets off.
  - HTTP/2 inherited from the image's http-level `http2 on`.
- `server_tokens off;` (set at file top level) removes nginx version disclosure.

### Security response headers (always)

| Header                      | Value                                                                                                                                                                                                                                                                   |
| --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Strict-Transport-Security` | `max-age=15552000; includeSubDomains`                                                                                                                                                                                                                                   |
| `X-Content-Type-Options`    | `nosniff`                                                                                                                                                                                                                                                               |
| `X-Frame-Options`           | `DENY`                                                                                                                                                                                                                                                                  |
| `Referrer-Policy`           | `no-referrer`                                                                                                                                                                                                                                                           |
| `Permissions-Policy`        | `camera=(), microphone=(), geolocation=(), payment=(), usb=(), magnetometer=(), gyroscope=(), accelerometer=(), fullscreen=(self)`                                                                                                                                      |
| `Content-Security-Policy`   | `default-src 'self'; script-src 'self' 'unsafe-inline' 'unsafe-eval'; style-src 'self' 'unsafe-inline'; img-src 'self' data: blob:; font-src 'self' data:; connect-src 'self' ws: wss:; frame-ancestors 'none'; base-uri 'self'; form-action 'self'; object-src 'none'` |

### Edge rate limiting (defence in depth)

Two `limit_req_zone` zones, evaluated _before_ the rule engine:

| Zone      | Rate      | Burst  | Applied to                                                                                                                                             |
| --------- | --------- | ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `auth`    | `2 r/s`   | `5`    | `/api/auth/login` and `/api/auth/signup` (anti-brute-force on credentials).                                                                            |
| `general` | `200 r/s` | varies | Everything else. Burst per location: `/` → 400 (Vite dev fans into many ESM module requests), `/api/` → 40, `/ai/` → 20, `/ai/(rag\|llm)/stream` → 10. |

These complement the application-layer limits in `back/src/middlewares/rateLimitMiddlewares.ts` (per-IP + per-email auth) and `slowapi` in the AI engine (`10/minute` on `/ai/rag/stream`).

### Body / timeout limits

| Directive               | Value | Reason                                                   |
| ----------------------- | ----- | -------------------------------------------------------- |
| `client_max_body_size`  | 1 MiB | Mirrors `MODSEC_REQ_BODY_LIMIT`. Matches HL7 64-KiB cap. |
| `client_body_timeout`   | 10 s  | Slowloris mitigation.                                    |
| `client_header_timeout` | 10 s  | Same.                                                    |
| `send_timeout`          | 30 s  |                                                          |
| `keepalive_timeout`     | 30 s  |                                                          |

### Forwarded headers

Every upstream (`/`, `/api/`, `/ai/`, `/ai/rag/stream`) receives `X-Real-IP`, `X-Forwarded-For`, `X-Forwarded-Proto`, and `X-Forwarded-Host`. Express runs with `app.set("trust proxy", 1)` so `req.ip` resolves to the real client and the per-IP auth rate-limit works correctly behind the WAF.

---

## 3. How to verify

### TLS / HTTPS-only

```bash
# 1. HTTPS works:
curl -kI https://localhost:8443/        # expect 200/302 and security headers
# 2. HTTP redirects:
curl -I  http://localhost:8080/         # expect 301 Location: https://...:8443/
curl -I  http://localhost:8080/api/auth/login   # expect 301
# 3. /health answers on both:
curl     http://localhost:8080/health   # "OK"
curl -k  https://localhost:8443/health  # "OK"
```

### WAF blocks an obvious attack

```bash
curl -ki "https://localhost:8443/?q=<script>alert(1)</script>"
# expect: 403 Forbidden (ModSecurity)
docker logs ft_waf 2>&1 | grep ModSecurity   # rule trigger visible in audit log
```

### Vault

```bash
docker exec ft_vault vault status
# Initialized: true   Sealed: false   Storage Type: file
docker logs ft_vault_init | tail -5
# expect: "AppRole authentication configured" and equivalent for ai-engine
```

### Rate limits hit

```bash
for i in $(seq 1 30); do curl -k -s -o /dev/null -w "%{http_code}\n" \
  -X POST https://localhost:8443/api/auth/login \
  -H 'Content-Type: application/json' -d '{}'; done
# expect: a wave of 4xx within the first burst, then 503/429 from nginx limit_req
```

---

## 4. Useful commands

| Action                         | Command                               |
| ------------------------------ | ------------------------------------- |
| Start the full stack           | `make up`                             |
| Tail WAF / audit logs          | `docker logs -f ft_waf`               |
| Tail Vault audit logs          | `docker logs -f ft_vault`             |
| Vault status                   | `docker exec ft_vault vault status`   |
| Re-run Vault init (idempotent) | `docker compose run --rm vault-init`  |
| Force model re-pull            | `docker compose run --rm ollama-init` |

---

## 5. What this satisfies in the subject

The _"Cybersecurity: WAF/ModSecurity (hardened) + HashiCorp Vault for secrets"_ major module asks for:

- **Strict ModSecurity / WAF configuration** — covered by paranoia 2, blocking on, anomaly thresholds 10/5, audit logging, body-size limits, edge rate limiting, full TLS hardening, and the response-header pack above.
- **Secrets managed in Vault, encrypted and isolated per service** — covered by the file-backend Vault, the per-service AppRole + KV path, and the strict volume isolation that keeps root credentials out of every app container.
