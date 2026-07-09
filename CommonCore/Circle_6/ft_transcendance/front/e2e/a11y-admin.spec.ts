import { test, expect } from "@playwright/test";
import AxeBuilder from "@axe-core/playwright";

/**
 * WCAG 2.1 AA accessibility audit for the Admin page.
 *
 * Flow:
 *   1. Log in as the seeded admin user.
 *   2. App redirects to Admin after successful login.
 *   3. Run axe-core on the Admin page.
 */

test.describe("Admin page accessibility", () => {
  test("admin page has no WCAG 2.1 AA violations", async ({ page }) => {
    await page.goto("/");
    // Wait for session rehydration to finish
    await expect(page.locator("text=Loading...")).not.toBeVisible();

    // Default seeded admin credentials (see docker-compose.yml)
    const adminEmail = "admin@admin.com";
    const adminPassword = "admin_password";

    // Step 1: fill login fields
    await page.locator("#input-mail").fill(adminEmail);
    await page.locator("#input-password").fill(adminPassword);

    // Step 2: click LOGIN
    await page.getByRole("button", { name: /LOGIN/i }).click();

    // Step 3: wait for redirect to Admin page
    await expect(page.getByLabel(/User Management List/i)).toBeVisible({ timeout: 10000 });
    await page.waitForTimeout(700);

    // Step 4: run accessibility audit
    const results = await new AxeBuilder({ page })
      .withTags(["wcag2a", "wcag2aa", "wcag21aa"])
      .analyze();

    expect(results.violations).toEqual([]);
  });
});
