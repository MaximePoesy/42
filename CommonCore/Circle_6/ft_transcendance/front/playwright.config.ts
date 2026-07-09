import { defineConfig, devices } from "@playwright/test";

/**
 * Playwright configuration for end-to-end accessibility testing.
 *
 * Prerequisites:
 *   docker compose up --build   (app must be running on https://localhost:8443)
 *
 * Run tests:
 *   npx playwright test           (headless)
 *   npx playwright test --ui      (interactive UI mode)
 *   npx playwright test --project=chromium --headed
 *
 * View report:
 *   npx playwright show-report
 */
export default defineConfig({
  testDir: "./e2e",
  fullyParallel: true,
  forbidOnly: !!process.env.CI,
  retries: process.env.CI ? 2 : 0,
  workers: process.env.CI ? 1 : undefined,
  reporter: [["html", { open: "never" }], ["list"]],
  use: {
    baseURL: "https://localhost:8443",
    ignoreHTTPSErrors: true,
    trace: "on-first-retry",
    screenshot: "only-on-failure",
  },
  projects: [
    {
      name: "chromium",
      use: { ...devices["Desktop Chrome"] },
    },
  ],
});
