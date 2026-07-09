import { useTranslation } from "react-i18next";

export default function PrivacyPolicyContent() {
  const { t } = useTranslation();

  return (
    <>
      <h3 className="text-lg font-semibold text-orange-300">{t("PP Introduction")}</h3>
      <p>{t("PP Introduction text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("PP Information We Collect")}</h3>
      <p>
        <strong>{t("PP Account Information")}</strong> {t("PP Account Information text")}
      </p>
      <p>
        <strong>{t("PP Medical Data")}</strong> {t("PP Medical Data text")}
      </p>

      <h3 className="text-lg font-semibold text-orange-300">
        {t("PP How We Use Your Information")}
      </h3>
      <ul className="list-disc pl-5 space-y-1">
        <li>{t("PP Use 1")}</li>
        <li>{t("PP Use 2")}</li>
        <li>{t("PP Use 3")}</li>
        <li>{t("PP Use 4")}</li>
      </ul>

      <h3 className="text-lg font-semibold text-orange-300">{t("PP Data Security")}</h3>
      <p>{t("PP Data Security text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("PP GDPR")}</h3>
      <p>{t("PP GDPR text")}</p>

      <h3 className="text-lg font-semibold text-orange-300">{t("PP Updates")}</h3>
      <p>{t("PP Updates text")}</p>
    </>
  );
}
