# WCAG 2.1 AA End-to-End Accessibility Tests

This folder contains Playwright + axe-core tests that prove the frontend meets WCAG 2.1 AA criteria.

## Prerequisites

The full application stack must be running:

```bash
docker compose down -v
docker compose up --build
```

The app will be available at `https://localhost:8443`.

## Run Tests

From the repository root:

```bash
# Headless (CI mode)
npm run test:e2e --workspace=front

# Interactive UI mode (great for debugging)
npm run test:e2e:ui --workspace=front

# View HTML report after a run
npm run test:e2e:report --workspace=front
```

Or from the `front/` directory:

```bash
npx playwright test
npx playwright test --ui
npx playwright show-report
```

## What Gets Tested

| Test file                | Page      | Auth required     | Description                                                              |
| ------------------------ | --------- | ----------------- | ------------------------------------------------------------------------ |
| `a11y-register.spec.ts`  | Register  | No                | Public landing page with login/signup forms, language switcher, and news |
| `a11y-principal.spec.ts` | Principal | Yes (signup)      | Logged-in user dashboard: file upload, AI chat, download, export         |
| `a11y-admin.spec.ts`     | Admin     | Yes (admin login) | Admin user management table, search, pagination, modals                  |

All tests assert `violations.length === 0` against the full WCAG 2.1 AA rule set (`wcag2a` + `wcag2aa` + `wcag21aa`).

## Interpreting Results

- **Pass** (`violations: []`) → zero accessibility issues found by axe-core.
- **Fail** → axe-core reports violations with exact element selectors, WCAG criterion references (e.g. `color-contrast`), and remediation guidance.

The HTML report includes screenshots on failure so you can see exactly what element triggered the violation.

## Notes

- Tests use a **unique timestamped email** for signup so they remain idempotent even if the database is not fully reset between runs.
- Admin credentials are the seeded defaults from `docker-compose.yml` (`admin@admin.com` / `admin_password`).
- Playwright is configured to ignore the self-signed certificate used in local development (`ignoreHTTPSErrors: true`).
