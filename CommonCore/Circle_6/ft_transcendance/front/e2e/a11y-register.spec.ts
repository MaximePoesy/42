import { test, expect } from "@playwright/test";
import AxeBuilder from "@axe-core/playwright";

/**
 * WCAG 2.1 AA accessibility audit for the public Register page.
 *
 * Covers:
 *   - Login form
 *   - Signup form (expanded)
 *   - Language switcher
 *   - News section
 *   - Footer links
 */

test.describe("Register page accessibility", () => {
  test("register page has no WCAG 2.1 AA violations", async ({ page }) => {
    await page.goto("/");
    // Wait for the page to be fully rendered (session rehydration finishes)
    await expect(page.locator("text=Loading...")).not.toBeVisible();
    await page.waitForTimeout(700);

    const results = await new AxeBuilder({ page })
      .withTags(["wcag2a", "wcag2aa", "wcag21aa"])
      .analyze();

    expect(results.violations).toEqual([]);
  });

  test("signup form expanded has no WCAG 2.1 AA violations", async ({ page }) => {
    await page.goto("/");
    await expect(page.locator("text=Loading...")).not.toBeVisible();
    await page.waitForTimeout(700);

    // Expand the signup form by clicking the SIGNUP button
    await page.getByRole("button", { name: /SIGN UP/i }).click();
    // Wait for the signup inputs to be visible
    await expect(page.locator("#input-name")).toBeVisible();

    const results = await new AxeBuilder({ page })
      .withTags(["wcag2a", "wcag2aa", "wcag21aa"])
      .analyze();

    expect(results.violations).toEqual([]);
  });
});
