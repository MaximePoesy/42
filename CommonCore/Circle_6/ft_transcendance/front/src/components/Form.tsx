import type { RefObject } from "react";
import { useTranslation } from "react-i18next";

import mailIcon from "../assets/mail.svg";
import passwordIcon from "../assets/password.svg";
import nameIcon from "../assets/name.svg";
import { EMAIL_MAX, NAME_MAX, PASSWORD_MAX } from "../uses/validators";

///////////////////////////////////////////////////
//////////////// FORMS EN GENERAL /////////////////
///////////////////////////////////////////////////

interface FormProp {
  icon: string;
  label: string;
  type: "email" | "password" | "text";
  placeholder?: string;
  inputRef?: RefObject<HTMLInputElement | null>;
  maxLength?: number;
  autoComplete?: string;
}

const loginForm: FormProp[] = [
  { icon: mailIcon, label: "MAIL", type: "email", maxLength: EMAIL_MAX, autoComplete: "email" },
  {
    icon: passwordIcon,
    label: "PASSWORD",
    type: "password",
    maxLength: PASSWORD_MAX,
    autoComplete: "current-password",
  },
];

const signupForm: FormProp[] = [
  { icon: nameIcon, label: "NAME", type: "text", maxLength: NAME_MAX, autoComplete: "given-name" },
  {
    icon: nameIcon,
    label: "LAST NAME",
    type: "text",
    maxLength: NAME_MAX,
    autoComplete: "family-name",
  },
];

const Form = ({ icon, label, type, placeholder, inputRef, maxLength, autoComplete }: FormProp) => {
  const { t } = useTranslation();
  const inputId = `input-${label.toLowerCase().replace(/\s+/g, "-")}`;
  return (
    <div>
      <label
        htmlFor={inputId}
        className="flex gap-3 pb-3 text-orange-300 font-medium cursor-pointer"
      >
        <img src={icon} alt="" className="w-6 h-6" aria-hidden="true" />
        {t(label)}
      </label>
      <div>
        <input
          id={inputId}
          ref={inputRef as RefObject<HTMLInputElement>}
          type={type}
          placeholder={placeholder ? t(placeholder) : ""}
          required
          maxLength={maxLength}
          autoComplete={autoComplete}
          className="text-orange-100 p-3 border-3 border-orange-700 rounded-lg max-w-xs bg-transparent focus:outline-none focus:ring-2 focus:ring-orange-400 placeholder:text-orange-600"
        />
      </div>
    </div>
  );
};

///////////////////////////////////////////////////
///////////////////// LOGIN FORM //////////////////
///////////////////////////////////////////////////

interface LoginFormProp {
  verificationMessage?: string;
  mailRef?: RefObject<HTMLInputElement | null>;
  passwordRef?: RefObject<HTMLInputElement | null>;
}

export const LoginForm = ({ verificationMessage, mailRef, passwordRef }: LoginFormProp) => {
  const getRef = (fieldName: string) => {
    if (fieldName === "MAIL") return mailRef;
    if (fieldName === "PASSWORD") return passwordRef;
    return undefined;
  };
  return (
    <div className="flex flex-col gap-7">
      <div aria-live="polite" className="sr-only">
        {verificationMessage}
      </div>
      {loginForm.map((field) => (
        <Form
          key={field.label}
          icon={field.icon}
          label={field.label}
          type={field.type}
          placeholder={""}
          inputRef={getRef(field.label)}
          maxLength={field.maxLength}
          autoComplete={field.autoComplete}
        />
      ))}
    </div>
  );
};

///////////////////////////////////////////////////
////////////////// SIGN IN FORM ///////////////////
///////////////////////////////////////////////////

interface SignupFormProp {
  nameRef?: RefObject<HTMLInputElement | null>;
  lastnameRef?: RefObject<HTMLInputElement | null>;
  verificationMessage?: string;
}

export const SignupForm = ({ nameRef, lastnameRef, verificationMessage }: SignupFormProp) => {
  const getRef = (fieldName: string) => {
    if (fieldName === "NAME") return nameRef;
    if (fieldName === "LAST NAME") return lastnameRef;
    return undefined;
  };

  return (
    <div className="flex flex-col gap-7">
      {/* Live region for signup validation errors */}
      <div aria-live="polite" className="sr-only">
        {verificationMessage}
      </div>
      {signupForm.map((field) => (
        <Form
          key={field.label}
          icon={field.icon}
          label={field.label}
          type={field.type}
          inputRef={getRef(field.label)}
          maxLength={field.maxLength}
          autoComplete={field.autoComplete}
        />
      ))}
    </div>
  );
};
