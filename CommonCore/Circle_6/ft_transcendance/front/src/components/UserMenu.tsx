import { useEffect, useRef, useState } from "react";
import { useTranslation } from "react-i18next";

interface UserMenuProps {
  isAdmin?: boolean;
  showAdminLink?: boolean;
  showHomeLink?: boolean;
  onGoToAdmin?: () => void;
  onGoToHome?: () => void;
  onExportData?: () => void;
  onDeleteAccount?: () => void;
  onLogout: () => void | Promise<void>;
}

export function UserMenu({
  isAdmin = false,
  showAdminLink = false,
  showHomeLink = false,
  onGoToAdmin,
  onGoToHome,
  onExportData,
  onDeleteAccount,
  onLogout,
}: UserMenuProps) {
  const { t } = useTranslation();
  const [open, setOpen] = useState(false);
  const menuRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const handleClickOutside = (event: MouseEvent) => {
      if (!menuRef.current) return;
      if (!menuRef.current.contains(event.target as Node)) {
        setOpen(false);
      }
    };

    const handleEscape = (event: KeyboardEvent) => {
      if (event.key === "Escape") {
        setOpen(false);
      }
    };

    document.addEventListener("mousedown", handleClickOutside);
    document.addEventListener("keydown", handleEscape);

    return () => {
      document.removeEventListener("mousedown", handleClickOutside);
      document.removeEventListener("keydown", handleEscape);
    };
  }, []);

  const handleAction = (action?: () => void | Promise<void>) => {
    setOpen(false);
    action?.();
  };

  return (
    <div ref={menuRef} className="relative inline-block text-left">
      <button
        type="button"
        onClick={() => setOpen((prev) => !prev)}
        aria-expanded={open}
        aria-haspopup="menu"
        className="px-4 py-2 rounded-lg border border-orange-600 bg-orange-800 text-orange-100 font-semibold hover:bg-orange-700 focus:outline-none focus:ring-2 focus:ring-orange-400"
      >
        {t("Menu")}
      </button>

      {open && (
        <div
          role="menu"
          aria-label={t("User menu")}
          className="absolute right-0 mt-2 w-56 overflow-hidden rounded-lg border border-orange-700 bg-orange-950 shadow-xl z-50"
        >
          {showAdminLink && isAdmin && (
            <button
              type="button"
              role="menuitem"
              onClick={() => handleAction(onGoToAdmin)}
              className="block w-full px-4 py-3 text-left text-orange-100 hover:bg-orange-900 focus:outline-none focus:bg-orange-900"
            >
              {t("Admin panel")}
            </button>
          )}

          {showHomeLink && (
            <button
              type="button"
              role="menuitem"
              onClick={() => handleAction(onGoToHome)}
              className="block w-full px-4 py-3 text-left text-orange-100 hover:bg-orange-900 focus:outline-none focus:bg-orange-900"
            >
              {t("Home")}
            </button>
          )}

          {onExportData && (
            <button
              type="button"
              role="menuitem"
              onClick={() => handleAction(onExportData)}
              className="block w-full px-4 py-3 text-left text-orange-100 hover:bg-orange-900 focus:outline-none focus:bg-orange-900"
            >
              {t("Export my data")}
            </button>
          )}

          {onDeleteAccount && (
            <button
              type="button"
              role="menuitem"
              onClick={() => handleAction(onDeleteAccount)}
              className="block w-full px-4 py-3 text-left text-red-200 hover:bg-red-900 focus:outline-none focus:bg-red-900"
            >
              {t("Delete account")}
            </button>
          )}

          <button
            type="button"
            role="menuitem"
            onClick={() => handleAction(onLogout)}
            className="block w-full px-4 py-3 text-left text-orange-100 hover:bg-orange-900 focus:outline-none focus:bg-orange-900"
          >
            {t("Logout")}
          </button>
        </div>
      )}
    </div>
  );
}
