import { useEffect, useRef } from "react";

const FOCUSABLE_SELECTORS = [
  "a[href]",
  "button:not([disabled])",
  "input:not([disabled])",
  "select:not([disabled])",
  "textarea:not([disabled])",
  '[tabindex]:not([tabindex="-1"])',
].join(", ");

/**
 * Traps keyboard focus inside a container when `isActive` is true.
 * - On activation: moves focus to the first focusable element inside the container.
 * - Tab / Shift+Tab cycles within the container only.
 * - On deactivation: returns focus to the element that was focused before the trap activated.
 *
 * Returns a ref to attach to the container element.
 */
export function useFocusTrap(isActive: boolean) {
  const containerRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    if (!isActive) return;

    const el = containerRef.current;
    if (!el) return;

    // Remember where focus was before the trap activated so we can restore it.
    const previouslyFocused = document.activeElement as HTMLElement | null;

    // Move focus into the container immediately.
    const firstFocusable = el.querySelectorAll<HTMLElement>(FOCUSABLE_SELECTORS)[0];
    firstFocusable?.focus();

    const handleKeyDown = (e: KeyboardEvent) => {
      if (e.key !== "Tab") return;

      const focusable = Array.from(el.querySelectorAll<HTMLElement>(FOCUSABLE_SELECTORS));
      if (focusable.length === 0) return;

      const first = focusable[0];
      const last = focusable[focusable.length - 1];

      if (e.shiftKey) {
        // Shift+Tab from the first element → wrap to last
        if (document.activeElement === first) {
          e.preventDefault();
          last.focus();
        }
      } else {
        // Tab from the last element → wrap to first
        if (document.activeElement === last) {
          e.preventDefault();
          first.focus();
        }
      }
    };

    document.addEventListener("keydown", handleKeyDown);

    return () => {
      document.removeEventListener("keydown", handleKeyDown);
      // Restore focus to the trigger element when the trap is deactivated.
      previouslyFocused?.focus();
    };
  }, [isActive]);

  return containerRef;
}
