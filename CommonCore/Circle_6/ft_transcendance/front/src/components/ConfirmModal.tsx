import { motion, AnimatePresence } from "framer-motion";
import { useEffect } from "react";
import { useTranslation } from "react-i18next";
import { useFocusTrap } from "../hooks/useFocusTrap";

interface ConfirmModalProps {
  isOpen: boolean;
  title: string;
  message: string;
  confirmLabel?: string;
  cancelLabel?: string;
  isDangerous?: boolean;
  onConfirm: () => void;
  onCancel: () => void;
  isLoading?: boolean;
}

export const ConfirmModal = ({
  isOpen,
  title,
  message,
  confirmLabel = "Confirm",
  cancelLabel = "Cancel",
  isDangerous = false,
  onConfirm,
  onCancel,
  isLoading = false,
}: ConfirmModalProps) => {
  const { t } = useTranslation();
  const dialogRef = useFocusTrap(isOpen);

  // Close on Escape
  useEffect(() => {
    if (!isOpen) return;
    const handleKeyDown = (e: KeyboardEvent) => {
      if (e.key === "Escape" && !isLoading) onCancel();
    };
    document.addEventListener("keydown", handleKeyDown);
    return () => document.removeEventListener("keydown", handleKeyDown);
  }, [isOpen, isLoading, onCancel]);

  return (
    <AnimatePresence>
      {isOpen && (
        <>
          {/* Backdrop — keyboard users dismiss via Escape, not by clicking */}
          <motion.div
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            onClick={isLoading ? undefined : onCancel}
            className="fixed inset-0 bg-black/60 z-40"
            aria-hidden="true"
          />
          {/* Dialog */}
          <motion.div
            initial={{ opacity: 0, scale: 0.9 }}
            animate={{ opacity: 1, scale: 1 }}
            exit={{ opacity: 0, scale: 0.9 }}
            transition={{ duration: 0.2 }}
            className="fixed inset-0 flex items-center justify-center z-50 p-4"
          >
            <div
              ref={dialogRef}
              role="dialog"
              aria-modal="true"
              aria-labelledby="confirm-modal-title"
              aria-describedby="confirm-modal-desc"
              onClick={(e) => e.stopPropagation()}
              className="bg-orange-900 border-3 border-orange-700 rounded-lg p-6 max-w-sm w-full shadow-lg"
            >
              <h2 id="confirm-modal-title" className="text-xl font-bold text-orange-100 mb-4">
                {title}
              </h2>
              <p id="confirm-modal-desc" className="text-orange-200 mb-6">
                {message}
              </p>
              <div className="flex gap-3 justify-end">
                <button
                  onClick={onCancel}
                  disabled={isLoading}
                  className="px-4 py-2 bg-orange-800 hover:bg-orange-700 border border-orange-600 rounded text-orange-100 font-semibold transition-colors disabled:opacity-50 cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400"
                  type="button"
                >
                  {cancelLabel}
                </button>
                <button
                  onClick={onConfirm}
                  disabled={isLoading}
                  aria-label={isLoading ? t("Loading") : confirmLabel}
                  className={`px-4 py-2 font-semibold rounded transition-colors disabled:opacity-50 cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400 ${
                    isDangerous
                      ? "bg-red-900 hover:bg-red-800 border border-red-700 text-red-100"
                      : "bg-orange-700 hover:bg-orange-600 border border-orange-600 text-orange-100"
                  }`}
                  type="button"
                >
                  {isLoading ? (
                    <span className="flex items-center gap-2">
                      <span
                        className="w-4 h-4 border-2 border-current border-t-transparent rounded-full animate-spin"
                        aria-hidden="true"
                      />
                      {t("Loading")}
                    </span>
                  ) : (
                    confirmLabel
                  )}
                </button>
              </div>
            </div>
          </motion.div>
        </>
      )}
    </AnimatePresence>
  );
};
