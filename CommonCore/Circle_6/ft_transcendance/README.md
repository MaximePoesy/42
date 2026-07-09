_This project has been created as part of the 42 curriculum by qlachena, staverni, chboegne, tcardair, mpoesy._

## Description

**ft_transcendance** is a secure, 3-tier web platform for medical data interoperability and AI-assisted querying. Healthcare professionals can ingest legacy HL7 v2 messages, convert them to the modern FHIR R4 standard, and interact with the resulting records through a locally-hosted Retrieval-Augmented Generation (RAG) pipeline — without any data leaving the host.

### Key Features

- HL7 v2 → FHIR R4 conversion engine (PID, PV1, OBX segments).
- Local RAG over ingested records, served by Ollama (`smollm2:135m`) with streaming responses (SSE) and per-IP rate limiting.
- Role-based admin console (search, sort, paginate, edit role, delete) gated by server-side `requireRole("admin")`.
- WCAG 2.1 AA compliance, automated via axe-core + Playwright and pa11y.
- Internationalisation (English, French, Spanish) with a persistent language switcher.
- GDPR self-service: account deletion + JSON export of personal data.
- Defence in depth: Nginx + ModSecurity (OWASP CRS) WAF as the only ingress; secrets fetched at boot from HashiCorp Vault over AppRole.

## Instructions

### Prerequisites

- Docker & Docker Compose v2
- GNU Make
- Node.js ≥ 20 + npm (used by `make setup` for local tooling: linting, pa11y, Playwright)
- OpenSSL (used by `make setup` to generate the self-signed TLS certificates)
- A copy of `.env.example` saved as `.env` at the repo root (defaults work for local dev)

Self-signed certs (`infra/certs/localhost.pem` / `localhost-key.pem`) are **generated
automatically** by `make` on first run — they are intentionally not committed.

### Run the stack

From the repository root:

```bash
make           # first run: generate certs, build & start everything (production images)
make up        # build & start every service in the background (production stack)
make dev       # development stack: bind mounts, hot reload, loopback debug ports, pgAdmin
make logs      # follow logs
make down      # stop the stack (either one)
make re        # full restart
make test      # run AI engine unit tests (requires the dev stack: prod images ship without tests)
make wcag      # run the WCAG 2.1 AA e2e suite against the running stack
```

The application is reachable at **https://localhost:8443/** (single ingress, served by the WAF). In production mode (`make up`) no other host port is published — `8080` only redirects to HTTPS. The dev stack (`make dev`) additionally exposes loopback-only debug ports (`5173`, `3001`, `8000`, `8201`, `11434`, `5050`); they are **not** the supported entry points.

`make up` is fully self-contained: Compose brings up the stack, the `vault-init` one-shot container provisions secrets, and the `ollama-init` one-shot container pulls the LLM (`smollm2:135m`) and embedding (`all-minilm`) models before the AI engine is allowed to start. First boot takes a few extra minutes while the models download; subsequent runs reuse the cached `ollama_data` volume.

### Default admin

A first admin account is seeded on boot from `ADMIN_EMAIL` / `ADMIN_PASSWORD` in `.env` (`.env.example` ships `admin@admin.com` / `admin_password`; the production stack refuses to boot without them, as it does for `DB_PASSWORD`). Override them before the first `make up`.

## Team Information

| Login      | Role(s)                                   | Responsibilities                                                                                                               |
| ---------- | ----------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `qlachena` | Tech Lead, AI/Backend Developer           | HL7→FHIR parser, FastAPI AI engine, RAG pipeline (ChromaDB + Ollama), Vault integration on the Python side, Architecture, i18n |
| `chboegne` | Project Manager, Frontend Developer       | React app, design                                                                                                              |
| `staverni` | Product Owner Fullstack Developer, DevOps | React app, express backend, session authentication, accessibility, WAF & Vault wiring, rate limiting.                          |
| `tcardair` | UX Manager                                | React app, design, user experience                                                                                             |
| `mpoesy`   | QA Developer / Tester                     | Pre-release quality pass: security bug hunting (API data-leak fix), regression fixes, i18n and test-suite corrections.         |

## Project Management

- **Branching:** trunk-based with short-lived `feature/*` branches merged and direct main.
- **Communication:** Discord for daily sync, school meeting.
- **Quality gates:** Prettier + ESLint husky hooks; Playwright + axe-core for accessibility; pytest for the AI engine.

## Technical Stack

| Layer          | Technology                                                                                | Why                                                                                        |
| -------------- | ----------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| Frontend       | React 19 + TypeScript, Vite 8, Tailwind v4, Framer Motion, react-i18next, vite-plugin-pwa | Modern, fast HMR, installable PWA, strong typing, simple styling primitives.               |
| Core backend   | Node.js, Express 5, TypeScript, TypeORM, Zod, argon2id, express-rate-limit, node-vault    | Mature ecosystem, ORM with explicit relations, strict env validation, memory-hard hashing. |
| AI/Data engine | Python 3, FastAPI, `hl7`, `fhir.resources`, ChromaDB, Ollama, slowapi, hvac               | CPU-friendly Python AI stack, strict pydantic validation, SSE streaming.                   |
| Storage        | PostgreSQL 15 (relational), ChromaDB (vectors)                                            | Battle-tested RDBMS + lightweight local vector DB — no cloud dependency.                   |
| Security       | Nginx + ModSecurity (OWASP CRS), HashiCorp Vault (file backend + AppRole)                 | Single ingress, blocks common payloads, runtime secret injection.                          |
| Observability  | pino-http (structured JSON logs)                                                          | Production-friendly log format.                                                            |
| Tooling        | Docker Compose, Make, Prettier, ESLint, Playwright, pytest, pa11y                         | Reproducible builds, single-command boot, deterministic checks.                            |

### Architectural choices

- **Microservices split:** `back` (Express) handles auth, sessions, RBAC, GDPR endpoints; `ai-engine` (FastAPI) handles HL7 parsing, vector store, and LLM streaming. The split isolates CPU-heavy AI work from request-bound API logic.
- **WAF-only ingress:** the only port the user touches is `8443`. All internal traffic stays on a private Docker bridge network.
- **Secrets via Vault AppRole:** services read role-id/secret-id from a private read-only volume mounted only by the consumer container; root credentials never leave the `vault-init` container.

## Database Schema

PostgreSQL, managed by TypeORM (`back/src/db/models/`).

```
┌─────────────────────────┐         ┌────────────────────────────┐
│ users                   │ 1     ∞ │ auth_attempts              │
├─────────────────────────┤◄────────┤────────────────────────────│
│ id           uuid PK    │         │ id           serial PK     │
│ email        varchar U  │         │ email        varchar       │
│ password     varchar    │         │ action       varchar       │
│ name         varchar    │         │ success      boolean       │
│ lastname     varchar    │         │ timestamp    timestamp     │
│ role         varchar    │         │ user_id      uuid FK NULL  │
│ created_at   timestamp  │         └────────────────────────────┘
└─────────────────────────┘
            ▲ 1
            │
            │ ∞
┌──────────────────────────┐
│ sessions                 │
├──────────────────────────┤
│ id           varchar PK  │
│ secret_hash  bytea       │
│ user_id      uuid FK     │ ON DELETE CASCADE
│ expires_at   timestamptz │
│ created_at   timestamptz │
└──────────────────────────┘
```

- `users.id` is a UUIDv7 generated server-side (lexicographically sortable, time-ordered).
- `sessions.secret_hash` stores a SHA-256 of the session secret; the raw token only lives in the user's HTTP-only cookie.
- `auth_attempts` records every login/signup attempt (success or failure) for audit and rate-limit forensics; deleting a user nulls the foreign key (`ON DELETE SET NULL`) so the audit trail survives.

## Features List

| Feature                                      | Implemented by         | Description                                                                  |
| -------------------------------------------- | ---------------------- | ---------------------------------------------------------------------------- |
| Email/password signup & login (argon2id)     | `staverni`             | `POST /api/auth/signup`, `POST /api/auth/login`, opaque session cookie.      |
| Session-backed auth + logout                 | `staverni`             | Server-stored sessions hashed with SHA-256, sliding expiry.                  |
| Admin console (list/edit/delete/role-change) | `chboegne`             | `front/src/pages/Admin.tsx`; protected by `requireRole("admin")`.            |
| Search / sort / paginate users               | `chboegne`             | Per-column filters, ascending/descending sort, pagination with aria-live.    |
| HL7 file ingestion in the browser            | `qlachena`             | `.hl7` selection, editable content area before conversion.                   |
| HL7 v2 → FHIR R4 conversion                  | `qlachena`             | `services/ai-engine/app/parsers/hl7_parser.py`, covered by `test_parser.py`. |
| RAG indexing + retrieval                     | `qlachena`             | ChromaDB persistent collection, populated on every successful conversion.    |
| Streaming LLM chat over records (SSE)        | `qlachena`, `staverni` | `/ai/rag/stream`, rate-limited 10/min/IP.                                    |
| Privacy Policy & Terms of Service modals     | `qlachena`             | Translated content, focus trap, ESC to close, accessible from the footer.    |
| WCAG 2.1 AA compliance                       | `staverni`             | Semantic landmarks, aria-live regions, skip-nav, axe-core CI test.           |
| i18n (EN/FR/ES) + persistent switcher        | `qlachena`             | `localStorage` keeps the choice; all UI strings go through `t(...)`.         |
| PWA (offline shell + installable)            | `qlachena`             | `vite-plugin-pwa` with autoUpdate.                                           |
| GDPR self-service (export + delete)          | `staverni`             | `/api/users/me/export`, `DELETE /api/users/me`, invalidates all sessions.    |
| Reverse proxy + ModSecurity WAF              | `staverni`, `chboegne` | OWASP CRS, single TLS ingress on `:8443`.                                    |
| Secret management via Vault (AppRole)        | `staverni`, `qlachena` | File backend, root creds isolated to the init container.                     |
| Rate limiting (auth + API + AI streaming)    | `staverni`             | `express-rate-limit` for the API, `slowapi` for the AI engine.               |
| API response sanitization (no password hash) | `mpoesy`               | `back/src/services/userMapper.ts`; safe-user projection on every endpoint.   |

## Modules

Total claimed: **22 points** (minimum required: 14).

### Major modules (×8 = 16 pts)

| Module                                         | Owner(s)               | Where to look                                                               |
| ---------------------------------------------- | ---------------------- | --------------------------------------------------------------------------- |
| Web — Framework front + back (2 pts)           | `staverni`, `chboegne` | `front/` (React+Vite), `back/` (Express), `services/ai-engine/` (FastAPI).  |
| Accessibility — WCAG 2.1 AA (2 pts)            | `staverni`             | Semantic HTML across `front/src/pages/`; `front/e2e/a11y-*.spec.ts`.        |
| User Management — Advanced permissions (2 pts) | `staverni`, `chboegne` | `back/src/middlewares/authMiddlewares.ts`, admin-only routes.               |
| AI — Complete RAG system (2 pts)               | `qlachena`             | `services/ai-engine/app/services/vector_store.py` + `/ai/rag(/stream)`.     |
| AI — Complete LLM interface (2 pts)            | `qlachena`, `staverni` | `services/ai-engine/app/services/ollama_client.py`, streaming + rate-limit. |
| Cybersecurity — WAF + Vault (2 pts)            | `staverni`, `qlachena` | `infra/nginx/`, `infra/waf/`, `infra/vault/`, `back/src/vaultConfig.ts`.    |
| DevOps — Backend as microservices (2 pts)      | `staverni`             | `docker-compose.yml`, two independently-built services.                     |
| Module of choice — HL7 → FHIR engine (2 pts)   | `qlachena`             | `services/ai-engine/app/parsers/hl7_parser.py`, `tests/test_parser.py`.     |

### Minor modules (×6 = 6 pts)

| Module                                              | Owner(s)               | Where to look                                                                    |
| --------------------------------------------------- | ---------------------- | -------------------------------------------------------------------------------- |
| Web — ORM (1 pt)                                    | `staverni`             | TypeORM entities in `back/src/db/models/`.                                       |
| Web — Custom design system, 10+ components (1 pt)   | `chboegne`             | `front/src/components/` (Button.tsx exports 9 variants alone).                   |
| Web — PWA, offline + installable (1 pt)             | `qlachena`             | `front/vite.config.ts` (VitePWA), service worker auto-registered.                |
| Web — Advanced search, filters/sort/paginate (1 pt) | `chboegne`             | `front/src/pages/Admin.tsx` + `useAdmin` hook.                                   |
| Accessibility & i18n — 3+ languages (1 pt)          | `qlachena`, `staverni` | `front/src/locales/{en,fr,es}/translation.json`, `front/src/i18n.ts`.            |
| Data & Analytics — GDPR (1 pt)                      | `qlachena`             | `back/src/routes/userRouter.ts` (`/me/export`, `DELETE /me`), email integration. |

### Module-of-choice justification — HL7 v2 → FHIR R4 engine

- **Why:** healthcare interop is the central use-case of the product. HL7 v2 is a 30-year-old pipe-delimited format that fights every modern parser; FHIR R4 is the JSON-first standard hospitals migrate to. Translating between them unlocks every downstream feature.
- **Technical challenges:** non-trivial escaping rules, optional segments, repeating fields, varying date formats, and strict FHIR resource validation. We use the `hl7` library to parse and `fhir.resources` (Pydantic) to validate the output, so a malformed segment surfaces as an explicit `HL7ParsingError` instead of corrupt data.
- **Value:** without this engine, the RAG pipeline would have nothing meaningful to index; with it, raw lab dumps become searchable, summarisable records.
- **Why Major:** non-trivial domain logic, real-world standard compliance, full test coverage (`services/ai-engine/tests/test_parser.py`), and the entry point for the rest of the AI pipeline.

## Individual Contributions

### `qlachena` — Tech Lead / AI & Backend Developer

- Owned the overall architecture and the module-of-choice: the HL7 v2 → FHIR R4 engine (PID/PV1/OBX), built on the `hl7` and `fhir.resources` libraries with a typed `HL7ParsingError` and pytest coverage in `services/ai-engine/tests/test_parser.py`.
- Built the FastAPI AI engine end-to-end: API surface (`/ai/convert`, `/ai/rag`, `/ai/rag/stream`, `/ai/chat`), Pydantic schemas, and Ollama client (chat, streaming, embedding helpers).
- Designed the RAG pipeline: human-readable FHIR summary generation, ChromaDB persistent collection, retrieval, and anti-hallucination prompt construction.
- Mirrored the Vault AppRole flow on the Python side (`services/ai-engine/app/services/vault_config.py`) so the AI engine reads its secrets the same way the Express backend does (co-owned with `staverni`).
- Wrote the i18n layer (`front/src/i18n.ts`) and authored the EN/FR/ES translation files, including the Privacy Policy and Terms of Service copy rendered by `PrivacyPolicyContent` and `TermsOfServiceContent`.
- Configured the PWA (`vite-plugin-pwa` in `front/vite.config.ts`, autoUpdate, offline shell, installable manifest).
- Owns the GDPR minor module — packaged and validated the `/api/users/me/export` and `DELETE /api/users/me` GDPR flows (with Ethereal email confirmations) end-to-end against the UI.
- _Challenge:_ smollm2:135m hallucinates on raw HL7 / FHIR JSON. Solved by indexing a natural-language **summary** of every bundle alongside the raw payload, so retrieval surfaces sentences the small model can actually reason about.

### `chboegne` — Project Manager / Frontend Developer

- Built the React admin console (`front/src/pages/Admin.tsx` + `useAdmin`): user listing, role change, deletion, and the confirmation modals around every destructive action.
- Implemented the advanced search module: per-column filters, ascending/descending sort with `aria-sort`, and accessible pagination with an `aria-live` page-status announcer.
- Crafted the design system (`front/src/components/`): the `Button` factory (9 button variants), `Form`, `ConfirmModal`, `LegalModal`, `Toast`, `LanguageSwitcher`, `ProtectedRoute`, `UserMenu` — every reusable surface the rest of the app composes from.
- Co-owned the User Management major module: built the admin-only UI and the role-gated views; `staverni` wired the matching server-side guards.
- Co-owned the WAF integration: tuned the OWASP CRS exclusion rules in `infra/waf/REQUEST-900-EXCLUSION-RULES-BEFORE-CRS.conf` so legitimate auth and AI payloads pass through.
- Ran the project rituals: backlog grooming, PR review rotation, release planning.
- _Challenge:_ keeping animated route transitions (Framer Motion) from breaking focus management — solved by funnelling every route into the `AnimatedPage` wrapper and pinning focus to `#main-content` on mount.

### `staverni` — Product Owner / Fullstack Developer / DevOps

- Wrote the Express backend: auth (`/api/auth/signup`, `/login`, `/logout`), password hashing with argon2id (`back/src/auth/password.ts`), session lifecycle (`back/src/auth/session.ts`), and per-IP + per-email rate limiting on auth endpoints.
- Defined the TypeORM models and relations (`User`, `Session`, `AuthAttempt`) with UUIDv7 generation and audit-trail-preserving cascades (`ON DELETE SET NULL` on `auth_attempts`, `ON DELETE CASCADE` on `sessions`).
- Implemented the GDPR backend endpoints (`/api/users/me/export`, `DELETE /api/users/me`) and the session-invalidation cascade that fires on account deletion.
- Drove WCAG 2.1 AA compliance across every page: semantic landmarks, `aria-live` announcements, skip-nav, focus management, and the axe-core + pa11y test harnesses in `front/e2e/a11y-*.spec.ts`.
- Designed the Docker Compose topology, the Nginx + ModSecurity WAF (`infra/nginx/`, single ingress on `:8443`), the Vault AppRole bootstrap (`infra/vault/`, `back/src/vaultConfig.ts`), and the SSE streaming plumbing (`proxy_buffering off`, chunked transfer disabled).
- Owns the microservices major module — the front/back/ai-engine/db/waf/vault topology with independent build and lifecycle.
- Co-owned the LLM streaming surface (SSE + rate limiting on `/ai/rag/stream`) and the i18n minor module (integrated the switcher into the WCAG-compliant footer).
- _Challenge:_ Vault initialisation race conditions across containers — solved with a dedicated `vault-init` one-shot container that writes AppRole files to a read-only volume mounted only by the consumer services, keeping root credentials isolated.

### `tcardair` — UX Manager

- Led the UI/UX redesign pass (`feature/UI-UX`), reworking the visual language across the main, register, and admin pages for a cleaner, less bulky layout.
- Built the `Logo` component (`front/src/components/Logo.tsx`) and wired it into the main page (`Principal.tsx`) and the register flow (`Register.tsx`).
- Created the `UserMenu` navigation component (`front/src/components/UserMenu.tsx`) so users can navigate and interact with account options from a single menu, backed by the `useAccountActions` hook (`front/src/uses/useAccountActions.tsx`).
- Redesigned the main page (`front/src/pages/Principal.tsx`): removed the bulky external frame, fixed footer overlap, and cut redundant buttons.
- Rebranded the product to **Confhirter** (`front/index.html`, README).
- _Challenge:_ tightening the layout without breaking the shared components — solved by consolidating navigation into a single reusable `UserMenu` and centralising account actions in one hook.

### `mpoesy` — QA Developer / Tester

- Ran the pre-release quality and security pass on the whole application, reviewing API responses, logs, and browser network traffic for leaks and regressions.
- Found and fixed a sensitive-data leak: the API returned each user's argon2 password hash inside the `user` objects consumed by the admin panel (visible in DevTools). Introduced `back/src/services/userMapper.ts`, a safe-user projection applied to every outgoing user payload.
- Fixed a race condition in `back/src/services/emailService.ts` where GDPR confirmation emails could be attempted before the Nodemailer transporter was initialised during the first seconds after boot.
- Fixed interpolated i18n messages (rate-limit and AI error toasts) that were not translated because their keys and `{{placeholders}}` were missing from the EN/FR/ES locale files.
- Corrected an incorrect unit-test assertion in the HL7 parser suite (`services/ai-engine/tests/test_parser.py`) and an input regression that prevented typing in the HL7 editing area.
- _Challenge:_ finding leaks that automated tests miss — solved by manually auditing real browser traffic (DevTools network tab) against every admin and account flow, then locking the fix in at the service layer so no future endpoint can reintroduce it.

## Resources & AI Usage

### Classic references

- HL7 v2.x specification — https://www.hl7.org/implement/standards/product_brief.cfm?product_id=185
- FHIR R4 — https://hl7.org/fhir/R4/
- OWASP ModSecurity Core Rule Set — https://coreruleset.org/ - https://github.com/coreruleset/modsecurity-crs-docker/blob/main/README.md
- HashiCorp Vault AppRole — https://developer.hashicorp.com/vault/docs/auth/approle
- WCAG 2.1 — https://www.w3.org/TR/WCAG21/
- Server-Sent Events (MDN) — https://developer.mozilla.org/en-US/docs/Web/API/Server-sent_events
- TypeORM docs — https://typeorm.io/
- React + Vite — https://vite.dev/guide/
- FastAPI — https://fastapi.tiangolo.com/

### AI usage statement

AI assistants (GitHub Copilot, ChatGPT, Claude) were used for:

- Debugging Docker networking and Compose dependency ordering.
- Drafting Tailwind utility combinations and Framer Motion transitions.
- Reviewing axe-core violation reports and suggesting semantic-HTML refactors.
- Generating boilerplate test fixtures for the HL7 parser.

AI was **not** used to author the HL7 → FHIR mapping, the RAG prompt design, the auth/session code, or the WAF/Vault configuration. Every team member can explain and modify the modules they own.

## Known Limitations

- The bundled certs are self-signed for local dev; production deployment requires real certificates.
- The seeded admin password is sourced from `.env` — change it before any non-local use.
- ChromaDB persistence lives in the AI engine's container volume; backing it up is left to the host.
