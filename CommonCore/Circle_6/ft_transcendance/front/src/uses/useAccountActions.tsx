import { useState } from "react";
import { useTranslation } from "react-i18next";
import { useAuth } from "../context/AuthContext";
import { useToastContext } from "../context/ToastContext";

export function useAccountActions() {
  const { t } = useTranslation();
  const { logout } = useAuth();
  const { addToast } = useToastContext();

  const [isDeleting, setIsDeleting] = useState(false);
  const [showDeleteConfirm, setShowDeleteConfirm] = useState(false);

  const handleExportData = async () => {
    try {
      const response = await fetch(`/api/users/me/export`, { credentials: "include" });
      if (response.ok) {
        const data = await response.json();
        const blob = new Blob([JSON.stringify(data, null, 2)], { type: "application/json" });
        const url = URL.createObjectURL(blob);
        const a = document.createElement("a");
        a.href = url;
        a.download = "personal_data.json";
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
        addToast(t("Personal data exported successfully!"), "success");
      } else {
        addToast(t("Failed to export data."), "error");
      }
    } catch {
      addToast(t("Network error while exporting data."), "error");
    }
  };

  const handleDeleteAccount = async () => {
    setIsDeleting(true);
    try {
      const response = await fetch(`/api/users/me`, {
        method: "DELETE",
        credentials: "include",
      });

      if (response.ok) {
        addToast(t("Account deleted. We will miss you!"), "success");
        setShowDeleteConfirm(false);
        await logout();
      } else {
        const data = await response.json().catch(() => ({}));
        addToast(t("Failed to delete account: ") + (data.error ?? response.statusText), "error");
        setIsDeleting(false);
      }
    } catch {
      addToast(t("Network error while deleting account."), "error");
      setIsDeleting(false);
    }
  };

  return {
    handleExportData,
    handleDeleteAccount,
    isDeleting,
    showDeleteConfirm,
    setShowDeleteConfirm,
  };
}
