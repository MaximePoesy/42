import { useState, useRef } from "react";
import { useTranslation } from "react-i18next";
import type { AuthUser } from "../context/AuthContext";
import { firstError, validateLogin, validateSignup } from "./validators";

///////////////////////////////////////////////////
////// CENTRALISATION DES DONNES + VERIF USER /////
///////////////////////////////////////////////////

type AuthApiResponse = {
  user?: AuthUser;
  error?: string;
};

export const useRegister = () => {
  const { t } = useTranslation();

  const [verificationMessage, setVerificationMessage] = useState("");
  const [messageStatus, setMessageStatus] = useState<"success" | "error" | "loading" | "">("");
  const [signupForm, setSignupForm] = useState(false);
  const [isRegister, setIsRegister] = useState(false);
  const [isAdmin, setIsAdmin] = useState(false);
  const [loggedInUser, setLoggedInUser] = useState<AuthUser | null>(null);
  const [isLoading, setIsLoading] = useState(false);

  const mailRef = useRef<HTMLInputElement>(null);
  const passwordRef = useRef<HTMLInputElement>(null);
  const nameRef = useRef<HTMLInputElement>(null);
  const lastnameRef = useRef<HTMLInputElement>(null);

  const getFormValues = () => {
    const values = {
      mail: mailRef.current?.value || "",
      password: passwordRef.current?.value || "",
      name: nameRef.current?.value || "",
      lastname: lastnameRef.current?.value || "",
    };
    return values;
  };

  const reportError = (message: string) => {
    setVerificationMessage(message);
    setMessageStatus("error");
    setIsLoading(false);
  };

  const handleButtonClick = async (buttonLabel: string) => {
    const formValues = getFormValues();
    setVerificationMessage(t("Loading..."));
    setMessageStatus("loading");
    setIsLoading(true);

    try {
      if (buttonLabel === "LOGIN") {
        const errors = validateLogin({
          email: formValues.mail,
          password: formValues.password,
        });
        const firstErr = firstError(errors);
        if (firstErr) {
          // Only collapse the signup form if validation passes — prevents losing
          // half-filled signup data when the user accidentally clicks LOGIN.
          reportError(t(firstErr));
          return;
        }
        setSignupForm(false);

        const response = await fetch("/api/auth/login", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({
            email: formValues.mail.trim().toLowerCase(),
            password: formValues.password,
          }),
          credentials: "include",
        });

        const data: AuthApiResponse = await response.json();

        if (response.ok && data.user) {
          setVerificationMessage(t("Success!"));
          setMessageStatus("success");
          setLoggedInUser(data.user);
          if (data.user.role === "admin") {
            setIsAdmin(true);
          } else {
            setIsRegister(true);
          }
        } else {
          setVerificationMessage(data.error || t("Login failed."));
          setMessageStatus("error");
        }
      } else if (buttonLabel === "SIGNUP") {
        setSignupForm(true);

        const errors = validateSignup({
          email: formValues.mail,
          password: formValues.password,
          name: formValues.name,
          lastname: formValues.lastname,
        });
        const firstErr = firstError(errors);
        if (firstErr) {
          reportError(t(firstErr));
          return;
        }

        const response = await fetch("/api/auth/signup", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({
            email: formValues.mail.trim().toLowerCase(),
            password: formValues.password,
            name: formValues.name.trim(),
            lastname: formValues.lastname.trim(),
          }),
          credentials: "include",
        });

        const data: AuthApiResponse = await response.json();

        if (response.ok && data.user) {
          setVerificationMessage(t("Success!"));
          setMessageStatus("success");
          setLoggedInUser(data.user);
          setIsRegister(true);
          setSignupForm(false);
        } else {
          setVerificationMessage(data.error || t("Signup failed."));
          setMessageStatus("error");
        }
      }
    } catch {
      setVerificationMessage(t("Network error."));
      setMessageStatus("error");
    } finally {
      setIsLoading(false);
    }
  };

  return {
    verificationMessage,
    messageStatus,
    signupForm,
    mailRef,
    passwordRef,
    nameRef,
    lastnameRef,
    handleButtonClick,
    isRegister,
    isAdmin,
    loggedInUser,
    isLoading,
  };
};
