# ♿ Accessibility Guide (WCAG 2.1 AA)

This document explains the accessibility measures implemented to meet **WCAG 2.1 level AA** standards in the `ft_transcendance` project.

---

## 1. Semantic Structure

The interface has been restructured to use semantic HTML5 tags instead of generic `<div>` tags:

- `<main>`: Identifies the primary content of each page.
- `<header>` / `<footer>`: Delimits navigation and meta-information areas.
- `<section>`: Groups logical features (e.g., AI Chat, Upload, User List).
- `<article>`: Used for each individual entry in the user list.
- `<nav>`: Identifies groups of action buttons.

---

## 2. Keyboard Navigation

The entire application is navigable without a mouse:

- **Focus Indicator**: Every interactive element has a clearly visible orange outline (`focus:ring-2`) when navigating with the `Tab` key.
- **Tab Order**: The order follows visual logic from left to right and top to bottom.
- **Shortcuts**: The `Enter` key validates forms and activates buttons.

---

## 3. Reading Assistance (Assistive Tech)

### Accessible Labels and Names

- **Hidden Labels (`sr-only`)**: Search fields and icon buttons have text labels invisible to the naked eye but read by screen readers.
- **ARIA Labels**: Complex buttons (Edit, Trash, etc.) use `aria-label` to describe their exact action.
- **Decorative Images**: Purely aesthetic icons are hidden from screen readers via `aria-hidden="true"`.

### Dynamic Regions (ARIA Live)

The following areas use `aria-live="polite"` to announce changes without interrupting the user:

- Success/error messages during authentication.
- AI-generated responses.

---

## 4. Contrast and Colors

- **High Contrast**: The theme uses light orange text (`#fdba74`) on a dark background (`#2c1009`), ensuring a contrast ratio greater than 4.5:1.
- **Color Independence**: Error messages do not rely solely on color (red/green) but also use explicit text ("Success", "Loading").

---

## 5. How to Test (Without sudo rights - 42 School)

On 42 school PCs, installing system software like Orca is impossible. Therefore, we use tools integrated into the project and the browser.

### Automated Test with Pa11y

The project includes **Pa11y**, a command-line accessibility auditor.

1. Launch the application (`make up`).
2. Run the test:
   ```bash
   make accessibility-test
   ```
   👉 This tool will scan the page and list all WCAG 2.1 AA errors found.

### Browser Tools (Chrome/Brave)

1. **Accessibility Tree**: Right-click an element -> Inspect -> **Accessibility** tab (next to Styles/Computed). You will see how the browser "presents" the element to a screen reader.
2. **Screen Reader Simulation**: Chrome has an official extension called "Screen Reader" that can be activated without administrator rights via the Chrome Web Store.
3. **Lighthouse**:
   - Press `F12`.
   - Go to the **Lighthouse** tab.
   - Check only **Accessibility** and click **Analyze page load**.
   - The target score is **> 90/100**.
