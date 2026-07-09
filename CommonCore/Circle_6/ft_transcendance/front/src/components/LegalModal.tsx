import { useEffect } from "react";
import { motion } from "framer-motion";
import { useTranslation } from "react-i18next";
import { useFocusTrap } from "../hooks/useFocusTrap";

interface Prop {
  title: string;
  content: React.ReactNode;
  onClose: () => void;
}

export default function LegalModal({ title, content, onClose }: Prop) {
  const { t } = useTranslation();
  const dialogRef = useFocusTrap(true); // always active when mounted

  // Close on Escape
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      if (e.key === "Escape") onClose();
    };
    document.addEventListener("keydown", handleKeyDown);
    return () => document.removeEventListener("keydown", handleKeyDown);
  }, [onClose]);

  return (
    <motion.div
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
      // fixed (not absolute) so it covers the viewport regardless of scroll
      className="fixed inset-0 z-50 flex items-center justify-center bg-black/60 backdrop-blur-sm p-4"
      aria-hidden="true"
    >
      <div
        ref={dialogRef}
        role="dialog"
        aria-modal="true"
        aria-labelledby="legal-modal-title"
        onClick={(e) => e.stopPropagation()}
        className="bg-orange-950 border-2 border-orange-700 rounded-lg p-6 max-w-3xl w-full max-h-[80vh] flex flex-col shadow-2xl text-orange-100"
      >
        <h2
          id="legal-modal-title"
          className="text-2xl font-bold mb-4 border-b border-orange-800 pb-2"
        >
          {title}
        </h2>
        <div className="overflow-y-auto flex-1 pr-2 space-y-4 text-sm leading-relaxed">
          {content}
        </div>
        <div className="mt-6 flex justify-end">
          <button
            onClick={onClose}
            className="px-6 py-2 bg-orange-800 hover:bg-orange-700 border border-orange-600 rounded text-white font-semibold transition-colors cursor-pointer focus:outline-none focus:ring-2 focus:ring-orange-400"
            type="button"
          >
            {t("Close")}
          </button>
        </div>
      </div>
    </motion.div>
  );
}
