import { useTranslation } from "react-i18next";

export default function TermsOfServiceContent() {
  const { t } = useTranslation();

  return (
    <>
      <h3 className="text-lg font-semibold text-orange-300">{t("TOS Acceptance")}</h3>
      <p>{t("TOS Acceptance text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("TOS Description")}</h3>
      <p>{t("TOS Description text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("TOS Conduct")}</h3>
      <ul className="list-disc pl-5 space-y-1">
        <li>
          <strong>{t("TOS Conduct 1 title")}</strong> {t("TOS Conduct 1 text")}
        </li>
        <li>
          <strong>{t("TOS Conduct 2 title")}</strong> {t("TOS Conduct 2 text")}
        </li>
        <li>
          <strong>{t("TOS Conduct 3 title")}</strong> {t("TOS Conduct 3 text")}
        </li>
      </ul>

      <h3 className="text-lg font-semibold text-orange-300">{t("TOS IP")}</h3>
      <p>{t("TOS IP text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("TOS Liability")}</h3>
      <p>{t("TOS Liability text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("TOS Termination")}</h3>
      <p>{t("TOS Termination text")}</p>
    </>
  );
}
