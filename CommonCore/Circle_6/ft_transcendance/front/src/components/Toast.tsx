import { motion, AnimatePresence } from "framer-motion";
import { useTranslation } from "react-i18next";
import type { Toast as ToastType } from "../hooks/useToast";

interface ToastProps {
  toast: ToastType;
  onRemove: (id: string) => void;
  index: number;
}

const bgColor: Record<ToastType["type"], string> = {
  success: "bg-green-900 border-green-700",
  error: "bg-red-900 border-red-700",
  info: "bg-orange-900 border-orange-700",
};
const textColor: Record<ToastType["type"], string> = {
  success: "text-green-100",
  error: "text-red-100",
  info: "text-orange-100",
};
// role="alert" for errors (assertive), role="status" for others (polite)
const ariaRole: Record<ToastType["type"], string> = {
  success: "status",
  error: "alert",
  info: "status",
};

const Toast = ({ toast, onRemove, index }: ToastProps) => {
  const { t } = useTranslation();
  const bottomOffset = 16 + index * 72;

  return (
    <motion.div
      key={toast.id}
      initial={{ opacity: 0, x: 100 }}
      animate={{ opacity: 1, x: 0 }}
      exit={{ opacity: 0, x: 100 }}
      transition={{ duration: 0.3 }}
      role={ariaRole[toast.type]}
      aria-live={toast.type === "error" ? "assertive" : "polite"}
      aria-atomic="true"
      style={{ bottom: bottomOffset }}
      className={`fixed right-4 max-w-xs w-72 p-4 border-2 rounded-lg z-50 flex items-start gap-2 ${bgColor[toast.type]} ${textColor[toast.type]}`}
    >
      {/* Message — visible and announced by the live region on this element */}
      <p className="text-sm font-medium flex-1">{toast.message}</p>

      {/* Separate dismiss button so the accessible name doesn't override the message */}
      <button
        onClick={() => onRemove(toast.id)}
        aria-label={t("Dismiss notification")}
        className="shrink-0 ml-2 opacity-70 hover:opacity-100 transition-opacity cursor-pointer focus:outline-none focus:ring-2 focus:ring-current rounded"
        type="button"
      >
        <span aria-hidden="true">×</span>
      </button>
    </motion.div>
  );
};

export const ToastContainer = ({
  toasts,
  onRemove,
}: {
  toasts: ToastType[];
  onRemove: (id: string) => void;
}) => {
  return (
    <AnimatePresence>
      {toasts.map((toast, index) => (
        <Toast key={toast.id} toast={toast} onRemove={onRemove} index={index} />
      ))}
    </AnimatePresence>
  );
};
