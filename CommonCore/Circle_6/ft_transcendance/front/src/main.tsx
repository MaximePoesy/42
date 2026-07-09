import "./index.css";
import "./i18n";
import { registerSW } from "virtual:pwa-register";
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import { BrowserRouter } from "react-router-dom";
import App from "./App.tsx";
import { AuthProvider } from "./context/AuthProvider";

// Chrome refuses service workers on origins with an untrusted certificate
// (our local certs are self-signed). Registering explicitly lets us absorb
// that failure instead of leaving an uncaught SecurityError in the console;
// the PWA works as soon as the cert is trusted.
registerSW({ immediate: true, onRegisterError: () => {} });

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <BrowserRouter>
      <AuthProvider>
        <App />
      </AuthProvider>
    </BrowserRouter>
  </StrictMode>,
);
