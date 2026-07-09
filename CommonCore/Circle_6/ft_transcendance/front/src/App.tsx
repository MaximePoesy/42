import { AnimatePresence, motion } from "framer-motion";
import { useState } from "react";
import { useTranslation } from "react-i18next";
import { Routes, Route, Navigate, useLocation } from "react-router-dom";
import Register from "./pages/Register";
import Principal from "./pages/Principal";
import Admin from "./pages/Admin";
import LegalModal from "./components/LegalModal";
import PrivacyPolicyContent from "./components/PrivacyPolicyContent";
import TermsOfServiceContent from "./components/TermsOfServiceContent";
import { LanguageSwitcher } from "./components/LanguageSwitcher";
import { ToastContainer } from "./components/Toast";
import { useToastContext } from "./context/ToastContext";
import { ToastProvider } from "./context/ToastProvider";
import { useAuth } from "./context/AuthContext";
import { ProtectedRoute } from "./components/ProtectedRoute";

const ConnectedToastContainer = () => {
  const { toasts, removeToast } = useToastContext();
  return <ToastContainer toasts={toasts} onRemove={removeToast} />;
};

const AnimatedPage = ({ children }: { children: React.ReactNode }) => (
  <motion.div
    initial={{ opacity: 0, filter: "blur(0px)" }}
    animate={{ opacity: 1, filter: "blur(0px)" }}
    exit={{ opacity: 0, filter: "blur(10px)" }}
    transition={{ duration: 0.5, ease: "easeInOut" }}
    className="absolute inset-0 w-full overflow-y-auto"
  >
    {children}
  </motion.div>
);

function App() {
  const { t } = useTranslation();
  const { user, isLoading: isLoadingSession } = useAuth();
  const location = useLocation();
  const [showModal, setShowModal] = useState<"privacy" | "tos" | null>(null);

  if (isLoadingSession) {
    return (
      <div
        role="status"
        aria-live="polite"
        aria-label={t("Loading...")}
        className="w-full h-screen bg-orange-950 flex items-center justify-center"
      >
        <div className="flex flex-col items-center gap-4">
          <div
            className="w-12 h-12 border-4 border-orange-400 border-t-orange-700 rounded-full animate-spin"
            aria-hidden="true"
          />
          <p className="text-orange-300 text-sm">{t("Loading...")}</p>
        </div>
      </div>
    );
  }

  return (
    <ToastProvider>
      {/* Skip to main content — wrapped in <nav> so axe "contained by landmarks" passes */}
      <nav aria-label={t("Skip navigation")}>
        <a
          href="#main-content"
          className="sr-only focus:not-sr-only focus:absolute focus:top-2 focus:left-2 focus:z-50 focus:px-4 focus:py-2 focus:bg-orange-800 focus:text-white focus:rounded focus:ring-2 focus:ring-orange-400"
        >
          {t("Skip to main content")}
        </a>
      </nav>
      <div className="relative w-full h-screen bg-orange-950 overflow-hidden pb-10">
        <AnimatePresence mode="wait">
          <Routes location={location} key={location.pathname}>
            <Route
              path="/login"
              element={
                user ? (
                  <Navigate to={user.role === "admin" ? "/admin" : "/"} replace />
                ) : (
                  <AnimatedPage>
                    <Register />
                  </AnimatedPage>
                )
              }
            />
            <Route
              path="/"
              element={
                <ProtectedRoute>
                  <AnimatedPage>
                    <Principal />
                  </AnimatedPage>
                </ProtectedRoute>
              }
            />
            <Route
              path="/admin"
              element={
                <ProtectedRoute requireRole="admin">
                  <AnimatedPage>
                    <Admin />
                  </AnimatedPage>
                </ProtectedRoute>
              }
            />
            <Route path="*" element={<Navigate to="/login" replace />} />
          </Routes>
        </AnimatePresence>

        <AnimatePresence>
          {showModal === "privacy" && (
            <LegalModal
              key="privacy"
              title={t("Privacy Policy")}
              content={<PrivacyPolicyContent />}
              onClose={() => setShowModal(null)}
            />
          )}
          {showModal === "tos" && (
            <LegalModal
              key="tos"
              title={t("Terms of Service")}
              content={<TermsOfServiceContent />}
              onClose={() => setShowModal(null)}
            />
          )}
        </AnimatePresence>

        <footer className="absolute bottom-2 w-full flex justify-center items-center gap-4 text-orange-200 text-sm z-40">
          <div>
            <button
              onClick={() => setShowModal("privacy")}
              aria-haspopup="dialog"
              aria-expanded={showModal === "privacy"}
              className="hover:text-white mx-2 underline cursor-pointer transition-colors focus:outline-none focus:ring-2 focus:ring-orange-400 rounded"
            >
              {t("Privacy Policy")}
            </button>
            <span className="text-orange-600">|</span>
            <button
              onClick={() => setShowModal("tos")}
              aria-haspopup="dialog"
              aria-expanded={showModal === "tos"}
              className="hover:text-white mx-2 underline cursor-pointer transition-colors focus:outline-none focus:ring-2 focus:ring-orange-400 rounded"
            >
              {t("Terms of Service")}
            </button>
          </div>
          <LanguageSwitcher />
        </footer>

        <ConnectedToastContainer />
      </div>
    </ToastProvider>
  );
}

export default App;
