# Simple project helper Makefile for Docker Compose workflows.
#
# Two stacks share one project (same volumes, same container names):
#   make up   -> PRODUCTION  (docker-compose.yml, default Dockerfile builds)
#   make dev  -> DEVELOPMENT (docker-compose.dev.yml, bind mounts + hot reload)
# Only one stack can run at a time; `make down` stops either.
NAME = ft_transcendance

COMPOSE     = docker compose
COMPOSE_DEV = docker compose -f docker-compose.dev.yml

# Model selection: e.g., make up LLM=normal
LLM ?= light
ifeq ($(LLM),normal)
  export LLM_MODEL=llama3.2:1b
else ifeq ($(LLM),heavy)
  export LLM_MODEL=llama3.1:8b
else
  export LLM_MODEL=smollm2:135m
endif

all: up

# Host node_modules are only needed for the dev workflow and the local test
# tooling (pa11y, playwright) — production builds run npm ci inside Docker.
setup:
	@echo "🍊 Installing project dependencies..."
	@cd front && npm install --silent
	@cd back && npm install --silent

# Generate the self-signed TLS certs the WAF needs. `up` depends on this so
# `make up` on a fresh clone never starts nginx without certs (and never lets
# the Docker daemon create infra/certs as a root-owned bind-mount directory).
certs:
	@if [ ! -f infra/certs/localhost.pem ] || [ ! -f infra/certs/localhost-key.pem ]; then \
		echo "🍊 Generating self-signed certificates for WAF..."; \
		mkdir -p infra/certs; \
		openssl req -x509 -newkey rsa:4096 -keyout infra/certs/localhost-key.pem -out infra/certs/localhost.pem -sha256 -days 365 -nodes -subj "/C=FR/ST=IDF/L=Paris/O=42/CN=localhost" 2>/dev/null; \
		chmod 644 infra/certs/localhost-key.pem infra/certs/localhost.pem; \
	fi

# --- Production stack (default) ---
up: certs
	@echo "🍊 Starting ft_transcendance (production)..."
	$(COMPOSE) up --build -d

# --- Development stack (bind mounts, hot reload, pgAdmin, debug ports) ---
dev: setup certs
	@echo "🍊 Starting ft_transcendance (development)..."
	$(COMPOSE_DEV) up --build -d

# --remove-orphans also stops containers that only exist in the other stack
# (e.g. pgAdmin when switching from dev to prod), since both share the project.
down:
	@echo "🍊 Stopping ft_transcendance..."
	$(COMPOSE) down --remove-orphans

logs:
	@echo "🍊 Showing logs..."
	$(COMPOSE) logs -f

dev-logs:
	@echo "🍊 Showing dev logs..."
	$(COMPOSE_DEV) logs -f

# Requires the DEV stack (`make dev`): the prod image ships without tests/
# (see services/ai-engine/.dockerignore) and without pytest.
test:
	@echo "🍊 Running AI Engine tests..."
	docker exec -e PYTHONPATH=/app ft_ai-engine pytest -v /app/tests/test_parser.py

accessibility-test:
	@echo "🍊 Running automated accessibility audit..."
	@cd front && ./node_modules/.bin/pa11y -c .pa11y-config.json https://localhost:8443

# No --with-deps: it shells out to sudo/apt-get (no root on school machines,
# no apt on Arch). The browser itself downloads to ~/.cache/ms-playwright
# without root, and the system libraries it needs are already present on the
# 42 Ubuntu images. If a lib is ever missing, Playwright names it explicitly.
wcag:
	@echo "🍊 Ensuring Playwright Chromium is installed..."
	@cd front && npx playwright install chromium
	@echo "🍊 Running WCAG 2.1 AA e2e tests..."
	@npm run ally:front

# Only removes THIS project's containers, volumes and locally-built images.
# Never use `docker system prune` here: it would wipe every other project
# on the machine (e.g. an evaluator's).
clean:
	@echo "🍊 Cleaning up ft_transcendance Docker resources..."
	$(COMPOSE) down -v --rmi local --remove-orphans

fclean: clean
	@docker system prune -a --force
	@docker volume prune

re: down all

dev-re: down dev

# Wipes the AI vector memory (ChromaDB collection of indexed HL7 records).
# GLOBAL: removes every patient's data at once — it is a dev/test convenience,
# not a per-user GDPR delete. Restarts ai-engine afterwards so the engine drops
# its stale in-memory handle and recreates a fresh, empty collection.
purge-ai:
	@echo "🍊 Purging AI vector memory (ChromaDB)..."
	-$(COMPOSE) run --rm --no-deps --entrypoint sh ai-engine -c 'rm -rf /app/db/chroma/* /app/db/chroma/.[!.]*'
	-$(COMPOSE) restart ai-engine

.PHONY: all setup certs up dev down logs dev-logs clean fclean re dev-re test accessibility-test wcag purge-ai
