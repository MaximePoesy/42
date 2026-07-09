import { EditButton } from "../components/Button";
import { DownloadButton } from "../components/Button";
import { UploadButton } from "../components/Button";
import { SendButton } from "../components/Button";
import { ConvertButton } from "../components/Button";
import { usePrincipal } from "../uses/usePrincipal";
import { useRef, useEffect } from "react";
import { useTranslation } from "react-i18next";
import { useAuth } from "../context/AuthContext";
import { ConfirmModal } from "../components/ConfirmModal";
import { UserMenu } from "../components/UserMenu";
import { useNavigate } from "react-router-dom";
import { useAccountActions } from "../uses/useAccountActions";
import { Logo } from "../components/Logo";

export default function Principal() {
  const { t } = useTranslation();
  const { user, logout } = useAuth();
  const navigate = useNavigate();

  const {
    uploadFileName,
    handleButtonClick,
    fileUploadRef,
    handleSelectedFile,
    convertFileName,
    handleConvertClick,
    fileContent,
    setFileContent,
    fileOutput,
    downloadFileName,
    setDownloadFileName,
    fileExtension,
    setFileExtension,
    handleDownloadClick,
    aiMessage,
    setAiMessage,
    aiResponse,
    isAiLoading,
    handleAiSend,
    isConverting,
    aiMode,
    setAiMode,
  } = usePrincipal();

  const {
    handleExportData,
    handleDeleteAccount,
    isDeleting,
    showDeleteConfirm,
    setShowDeleteConfirm,
  } = useAccountActions();

  const fileContentEditableRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const el = fileContentEditableRef.current;
    if (!el) return;
    const current = el.innerText;
    const next = fileContent || "";
    if (current !== next) {
      el.innerText = next;
    }
  }, [fileContent]);

  return (
    <main
      id="main-content"
      tabIndex={-1}
      className="min-h-screen flex flex-col p-3 md:p-5 bg-orange-950"
    >
      <div className="flex items-center justify-between pt-4 pr-2 md:pr-5">
        <div className="hidden md:block w-40" />
        <div className="flex-1 flex justify-center">
          <Logo />
        </div>
        <div className="w-auto md:w-40 flex justify-end">
          <UserMenu
            isAdmin={user?.role === "admin"}
            showAdminLink={true}
            onGoToAdmin={() => navigate("/admin")}
            onExportData={handleExportData}
            onDeleteAccount={() => setShowDeleteConfirm(true)}
            onLogout={logout}
          />
        </div>
      </div>
      <div className="flex-1 flex flex-col lg:flex-row gap-5 p-3 md:p-5">
        <div className="w-full lg:w-1/2 min-w-0 flex flex-col gap-5">
          <section
            className="min-h-75 lg:h-1/2 flex flex-col gap-5 p-4 md:p-5 border-3 border-orange-800 rounded-lg"
            aria-label={t("File Upload and Processing")}
          >
            <div className="flex flex-wrap w-full gap-3">
              <input
                type="text"
                aria-label={t("Current selected file")}
                aria-readonly="true"
                className="flex-1 min-w-30 font-bold text-orange-300 border-3 border-orange-700 rounded-lg p-1 bg-transparent focus:outline-none focus:ring-4 focus:ring-orange-400"
                value={uploadFileName}
                readOnly
                placeholder={t("Upload a file")}
              />
              <UploadButton onButtonClick={() => handleButtonClick(fileUploadRef)} />
              <label className="sr-only" htmlFor="file-upload">
                {t("Upload HL7 file")}
              </label>
              <input
                id="file-upload"
                type="file"
                ref={fileUploadRef}
                className="hidden"
                onChange={handleSelectedFile}
                accept=".hl7"
              />
              <input
                type="text"
                aria-label={t("Decryption status")}
                aria-readonly="true"
                className="flex-1 min-w-30 font-bold text-orange-300 border-3 border-orange-700 rounded-lg p-1 bg-transparent focus:outline-none focus:ring-4 focus:ring-orange-400"
                value={convertFileName}
                readOnly
                placeholder={t("Decrypt")}
              />
              <ConvertButton
                onButtonClick={handleConvertClick}
                isLoading={isConverting}
                disabled={isConverting}
              />
            </div>
            <div className="relative flex-1 min-h-37.5">
              <div
                ref={fileContentEditableRef}
                role="textbox"
                aria-label={t("File content editor")}
                aria-placeholder={t("No selected file")}
                aria-multiline="true"
                className="absolute inset-0 overflow-auto text-orange-200 whitespace-pre outline-none focus:ring-4 focus:ring-orange-400 p-2 rounded-lg border border-transparent"
                contentEditable={true}
                onInput={(e) => setFileContent(e.currentTarget.innerText)}
                suppressContentEditableWarning={true}
                tabIndex={0}
              />
            </div>
          </section>
          <section
            className="min-h-75 lg:h-1/2 flex flex-col p-4 md:p-5 gap-5 border-3 border-orange-800 rounded-lg"
            aria-label={t("Results and Export")}
          >
            <div className="w-full flex flex-wrap gap-3 md:gap-5 items-center">
              <label className="sr-only" htmlFor="download-filename">
                {t("Export filename")}
              </label>
              <input
                id="download-filename"
                type="text"
                className="flex-1 min-w-30 font-bold text-orange-300 border-3 border-orange-700 rounded-lg p-1 bg-transparent focus:outline-none focus:ring-4 focus:ring-orange-400"
                value={downloadFileName}
                onChange={(e) => setDownloadFileName(e.target.value)}
                placeholder={t("File name")}
              />
              <span className="text-orange-300 font-bold text-3xl" aria-hidden="true">
                .
              </span>
              <label className="sr-only" htmlFor="download-extension">
                {t("Export extension")}
              </label>
              <input
                id="download-extension"
                type="text"
                className="w-20 md:w-1/4 font-bold text-orange-300 border-3 border-orange-700 rounded-lg p-1 bg-transparent focus:outline-none focus:ring-4 focus:ring-orange-400"
                value={fileExtension}
                onChange={(e) => setFileExtension(e.target.value)}
                placeholder={t("ext")}
              />
              <DownloadButton onButtonClick={handleDownloadClick} />
            </div>
            <div className="relative flex-1 min-h-37.5">
              <div
                role="region"
                aria-label={t("Generated output preview")}
                className="absolute inset-0 overflow-auto text-orange-200 p-2 focus:outline-none focus:ring-4 focus:ring-orange-400 rounded-lg whitespace-pre"
                tabIndex={0}
              >
                {fileOutput}
              </div>
            </div>
          </section>
        </div>
        <section
          className="min-h-100 lg:h-auto w-full lg:w-1/2 min-w-0 flex flex-col p-4 md:p-5 gap-5 border-3 border-orange-800 rounded-lg"
          aria-label={t("AI Assistant")}
        >
          <fieldset className="flex flex-wrap items-center gap-3">
            <legend className="sr-only">{t("AI mode")}</legend>
            <span className="text-orange-300 text-sm font-semibold" aria-hidden="true">
              {t("Mode:")}
            </span>
            {(["records", "general"] as const).map((mode) => {
              const isActive = aiMode === mode;
              const label = mode === "records" ? t("Records") : t("General");
              return (
                <label
                  key={mode}
                  className={`px-3 py-1 rounded-lg border-2 text-sm font-semibold cursor-pointer transition-colors focus-within:ring-2 focus-within:ring-orange-400 ${
                    isActive
                      ? "bg-orange-700 border-orange-500 text-white"
                      : "bg-transparent border-orange-800 text-orange-300 hover:bg-orange-900"
                  }`}
                >
                  <input
                    type="radio"
                    name="ai-mode"
                    value={mode}
                    checked={isActive}
                    onChange={() => setAiMode(mode)}
                    disabled={isAiLoading}
                    className="sr-only"
                  />
                  {label}
                </label>
              );
            })}
            <span className="text-orange-400 text-xs italic" aria-live="polite">
              {aiMode === "records"
                ? t("Answers grounded in your ingested records.")
                : t("Answers from the model's own knowledge (no records used).")}
            </span>
          </fieldset>
          <div className="relative flex-1 min-h-50">
            <div
              role="log"
              aria-live="polite"
              className="absolute inset-0 overflow-auto text-orange-200 whitespace-pre-wrap p-2 border border-orange-900 rounded focus:outline-none focus:ring-4 focus:ring-orange-400"
              tabIndex={0}
            >
              {aiResponse || t("AI responses will appear here.")}
            </div>
          </div>
          <div className="flex gap-3 md:gap-5">
            <label className="sr-only" htmlFor="ai-query">
              {t("Ask the medical AI")}
            </label>
            <textarea
              id="ai-query"
              className="h-20 md:h-25 min-w-0 flex-1 resize-none text-orange-200 whitespace-normal wrap-break-word border-3 border-orange-700 rounded-lg p-1 bg-transparent focus:outline-none focus:ring-4 focus:ring-orange-400"
              placeholder={
                aiMode === "records"
                  ? t("Ask about the records you have ingested")
                  : t("Ask a general medical or interoperability question")
              }
              value={aiMessage}
              onChange={(e) => setAiMessage(e.target.value)}
              onKeyDown={(e) => {
                if (e.key === "Enter" && !e.shiftKey) {
                  e.preventDefault();
                  handleAiSend();
                }
              }}
              disabled={isAiLoading}
            />
            <div
              role="group"
              aria-label={t("AI actions")}
              className="h-20 md:h-25 flex flex-col gap-3 md:gap-5"
            >
              <SendButton
                onButtonClick={handleAiSend}
                isLoading={isAiLoading}
                disabled={isAiLoading}
              />
              <EditButton onButtonClick={() => setAiMessage("")} />
            </div>
          </div>
        </section>
      </div>
      <ConfirmModal
        isOpen={showDeleteConfirm}
        title={t("Delete Account")}
        message={t(
          "Are you sure you want to delete your account? This action is permanent and cannot be undone.",
        )}
        confirmLabel={t("Delete")}
        cancelLabel={t("Cancel")}
        isDangerous={true}
        isLoading={isDeleting}
        onConfirm={handleDeleteAccount}
        onCancel={() => setShowDeleteConfirm(false)}
      />
    </main>
  );
}
