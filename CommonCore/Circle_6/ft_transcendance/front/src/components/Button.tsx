import { useTranslation } from "react-i18next";
import loginIcon from "../assets/login.svg";
import logoutIcon from "../assets/logout.svg";
import signupIcon from "../assets/signup.svg";

import uploadIcon from "../assets/upload.svg";
import downloadIcon from "../assets/download.svg";
import editIcon from "../assets/edit.svg";
import convertIcon from "../assets/convert.svg";
import sendIcon from "../assets/send.svg";
import trashIcon from "../assets/trash.svg";

type Var = "register" | "principal";

interface Prop {
  icon: string;
  label: string;
  onClick: () => void;
  variant?: Var;
  isLoading?: boolean;
  disabled?: boolean;
  /** Optional override for the button's accessible label (e.g. per-row context in a table) */
  ariaLabel?: string;
}

interface Click {
  onButtonClick?: (buttonLabel: string) => void;
  isLoading?: boolean;
  disabled?: boolean;
  /** Optional accessible label override */
  ariaLabel?: string;
}

const baseClass = `
  flex flex-col items-center justify-center
  border-2 border-orange-600
  bg-linear-to-b from-orange-500 to-orange-700
  text-orange-200
  rounded-lg
  shadow-md
  shrink-0
  transition-all duration-200 ease-in-out
  hover:from-orange-400 hover:to-orange-600
  active:translate-y-0.5 active:shadow-sm
  focus:outline-none focus:ring-4 focus:ring-orange-400 focus:ring-offset-2 focus:ring-offset-orange-950
`;

const variantClass: Record<Var, string> = {
  register: "w-17 h-15 text-sm font-medium gap-1",
  principal: "w-10 h-10",
};

const handleButtonClick = (label: string, onButtonClick?: (buttonLabel: string) => void) => {
  onButtonClick?.(label);
};

const IconButton = ({
  icon,
  label,
  onClick,
  variant = "principal",
  isLoading = false,
  disabled = false,
  ariaLabel,
}: Prop) => {
  const { t } = useTranslation();

  const isDisabled = isLoading || disabled;
  const accessibleLabel = ariaLabel ?? (isLoading ? t("Loading") : t(label));

  return (
    <button
      onClick={onClick}
      disabled={isDisabled}
      className={`${baseClass} ${variantClass[variant]} ${isDisabled ? "opacity-50 cursor-not-allowed" : ""}`}
      aria-label={accessibleLabel}
      type="button"
    >
      {isLoading ? (
        // Spinner — aria-hidden because the button's aria-label already says "Loading"
        <span
          aria-hidden="true"
          className="w-7 h-7 border-2 border-orange-300 border-t-orange-600 rounded-full animate-spin block"
        />
      ) : (
        // Icon is purely decorative; the button's aria-label is the accessible name
        <img
          src={icon}
          alt=""
          aria-hidden="true"
          className={variant === "register" ? "w-6 h-6" : "w-7 h-7"}
        />
      )}
      {variant === "register" && <span aria-hidden="true">{t(label)}</span>}
    </button>
  );
};

export const LoginButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={loginIcon}
    label="LOGIN"
    onClick={() => handleButtonClick("LOGIN", onButtonClick)}
    variant="register"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const SignupButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={signupIcon}
    label="SIGNUP"
    onClick={() => handleButtonClick("SIGNUP", onButtonClick)}
    variant="register"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const LogoutButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={logoutIcon}
    label="LOGOUT"
    onClick={() => handleButtonClick("LOGOUT", onButtonClick)}
    variant="register"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const EditButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={editIcon}
    label="EDIT"
    onClick={() => handleButtonClick("EDIT", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const DownloadButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={downloadIcon}
    label="DOWNLOAD"
    onClick={() => handleButtonClick("DOWNLOAD", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const UploadButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={uploadIcon}
    label="UPLOAD"
    onClick={() => handleButtonClick("UPLOAD", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const ConvertButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={convertIcon}
    label="CONVERT"
    onClick={() => handleButtonClick("CONVERT", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const SendButton = ({ onButtonClick, isLoading = false, disabled = false }: Click) => (
  <IconButton
    icon={sendIcon}
    label="SEND"
    onClick={() => handleButtonClick("SEND", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
  />
);

export const TrashButton = ({
  onButtonClick,
  isLoading = false,
  disabled = false,
  ariaLabel,
}: Click) => (
  <IconButton
    icon={trashIcon}
    label="TRASH"
    onClick={() => handleButtonClick("TRASH", onButtonClick)}
    variant="principal"
    isLoading={isLoading}
    disabled={disabled}
    ariaLabel={ariaLabel}
  />
);
