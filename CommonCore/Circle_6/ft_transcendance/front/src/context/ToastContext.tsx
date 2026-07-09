import { createContext, useContext } from "react";
import type { useToast } from "../hooks/useToast";

export type ToastContextType = ReturnType<typeof useToast>;

export const ToastContext = createContext<ToastContextType | undefined>(undefined);

export const useToastContext = () => {
  const context = useContext(ToastContext);
  if (!context) {
    throw new Error("useToastContext must be used within ToastProvider");
  }
  return context;
};
