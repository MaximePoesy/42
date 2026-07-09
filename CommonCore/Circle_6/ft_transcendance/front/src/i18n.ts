import i18n from "i18next";
import { initReactI18next } from "react-i18next";

import enTranslation from "./locales/en/translation.json";
import frTranslation from "./locales/fr/translation.json";
import esTranslation from "./locales/es/translation.json";

const resources = {
  en: { translation: enTranslation.translation },
  fr: { translation: frTranslation.translation },
  es: { translation: esTranslation.translation },
};

i18n.use(initReactI18next).init({
  resources,
  lng: localStorage.getItem("language") || "en",
  fallbackLng: "en",
  interpolation: {
    escapeValue: false, // react already safes from xss
  },
});

export default i18n;
