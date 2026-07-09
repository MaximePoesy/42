import { LoginForm } from "../components/Form";
import { SignupForm } from "../components/Form";
import { SignupButton } from "../components/Button";
import { LoginButton } from "../components/Button";
import { useRegister } from "../uses/useRegister";
import { useEffect } from "react";
import { useTranslation } from "react-i18next";
import { useAuth } from "../context/AuthContext";
import { Logo } from "../components/Logo";

export default function Register() {
  const { t } = useTranslation();
  const { login } = useAuth();
  const {
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
  } = useRegister();

  useEffect(() => {
    if ((isRegister || isAdmin) && loggedInUser) {
      login(loggedInUser);
    }
  }, [isRegister, isAdmin, loggedInUser, login]);

  const getMessageColor = () => {
    if (messageStatus === "success") return "text-green-300";
    if (messageStatus === "error") return "text-red-300";
    return "text-orange-300";
  };

  return (
    <main id="main-content" tabIndex={-1} className="min-h-screen p-3 md:p-5 bg-orange-950">
      <div className="flex items-center justify-center pt-4">
        <Logo />
      </div>

      <div className="flex justify-center items-center p-3 md:p-5 pt-4 min-h-[calc(100vh-6rem)]">
        <div className="flex items-center w-full md:w-auto">
          <section
            className={`flex flex-col h-auto md:h-125 border-3 border-orange-800 rounded-lg p-4 md:p-5 transition-all duration-1500 ease-in-out w-full ${signupForm ? "md:w-150" : "md:w-75"} relative overflow-hidden`}
            aria-label={t("Authentication")}
          >
            <div className="flex flex-col h-full">
              <div className="flex flex-col md:flex-row">
                <div
                  className={`flex justify-center transition-all duration-1500 ease-in-out ${signupForm ? "md:w-1/2" : "w-full"}`}
                >
                  <LoginForm
                    verificationMessage={verificationMessage}
                    mailRef={mailRef}
                    passwordRef={passwordRef}
                  />
                </div>
                <div
                  className={`flex justify-center transition-all duration-1500 ease-in-out ${signupForm ? "md:w-1/2 opacity-100" : "w-0 opacity-0 h-0 md:h-auto"} overflow-hidden`}
                >
                  <SignupForm
                    nameRef={nameRef}
                    lastnameRef={lastnameRef}
                    verificationMessage={verificationMessage}
                  />
                </div>
              </div>

              {verificationMessage && (
                <div
                  className={`text-center mb-4 p-2 rounded ${getMessageColor()} font-semibold text-sm`}
                  aria-live="polite"
                  aria-atomic="true"
                >
                  {verificationMessage}
                </div>
              )}

              <div
                role="group"
                aria-label={t("Authentication actions")}
                className="flex justify-around h-full items-center w-full"
              >
                <LoginButton onButtonClick={handleButtonClick} isLoading={isLoading} />
                <SignupButton onButtonClick={handleButtonClick} isLoading={isLoading} />
              </div>
            </div>
          </section>
        </div>
      </div>
    </main>
  );
}
