import { test, expect } from "@playwright/test";
import AxeBuilder from "@axe-core/playwright";

/**
 * WCAG 2.1 AA accessibility audit for the Principal (logged-in user) page.
 *
 * Flow:
 *   1. Sign up a new test user via the UI.
 *   2. App redirects to Principal after successful signup.
 *   3. Run axe-core on the Principal page.
 */

test.describe("Principal page accessibility", () => {
  test("principal page has no WCAG 2.1 AA violations", async ({ page }) => {
    await page.goto("/");
    // Wait for session rehydration to finish
    await expect(page.locator("text=Loading...")).not.toBeVisible();

    const timestamp = Date.now();
    const testEmail = `a11y-user-${timestamp}@test.com`;
    const testPassword = "TestPass123!";

    // Step 1: fill login-side fields
    await page.locator("#input-mail").fill(testEmail);
    await page.locator("#input-password").fill(testPassword);

    // Step 2: click SIGNUP to expand the signup form
    await page.getByRole("button", { name: /SIGN UP/i }).click();

    // Wait for the signup form to expand (name/lastname inputs visible)
    await expect(page.locator("#input-name")).toBeVisible();
    await expect(page.locator("#input-last-name")).toBeVisible();

    // Step 3: fill signup fields
    await page.locator("#input-name").fill("A11Y");
    await page.locator("#input-last-name").fill("Tester");

    // Step 4: click SIGNUP again to submit
    await page.getByRole("button", { name: /SIGN UP/i }).click();

    // Step 5: wait for redirect to Principal page
    // Principal page has a section labelled "File Upload and Processing"
    await expect(page.getByLabel(/File Upload and Processing/i)).toBeVisible({ timeout: 10000 });
    await page.waitForTimeout(700);

    // Step 6: run accessibility audit
    const results = await new AxeBuilder({ page })
      .withTags(["wcag2a", "wcag2aa", "wcag21aa"])
      .analyze();

    expect(results.violations).toEqual([]);
  });
});
