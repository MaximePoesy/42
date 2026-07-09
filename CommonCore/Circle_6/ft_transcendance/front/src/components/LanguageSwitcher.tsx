import React from "react";
import { useTranslation } from "react-i18next";

const LANGUAGES = [
  { code: "en", label: "EN", name: "English" },
  { code: "fr", label: "FR", name: "Français" },
  { code: "es", label: "ES", name: "Español" },
] as const;

export const LanguageSwitcher: React.FC = () => {
  const { i18n, t } = useTranslation();

  const changeLanguage = (lng: string) => {
    i18n.changeLanguage(lng);
    localStorage.setItem("language", lng);
  };

  return (
    <div role="radiogroup" aria-label={t("Select language")} className="flex gap-2">
      {LANGUAGES.map(({ code, label, name }) => {
        const isActive = i18n.language === code;
        return (
          <button
            key={code}
            role="radio"
            aria-checked={isActive}
            aria-label={name}
            onClick={() => changeLanguage(code)}
            className={`px-2 py-1 text-sm rounded transition-colors focus:outline-none focus:ring-2 focus:ring-orange-400 ${
              isActive ? "bg-orange-700 text-white" : "bg-orange-800 text-white hover:bg-orange-700"
            }`}
            type="button"
          >
            {label}
          </button>
        );
      })}
    </div>
  );
};
