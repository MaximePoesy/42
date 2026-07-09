import { useCallback, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext, type AuthUser } from "./AuthContext";

export const AuthProvider = ({ children }: { children: React.ReactNode }) => {
  const navigate = useNavigate();
  const [user, setUser] = useState<AuthUser | null>(null);
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    const rehydrateSession = async () => {
      try {
        // /api/auth/session answers 200 with user: null when anonymous, so a
        // logged-out visit never logs a 401 in the browser console.
        const response = await fetch("/api/auth/session", {
          method: "GET",
          credentials: "include",
        });
        if (response.ok) {
          const data = await response.json();
          setUser(data.user ?? null);
        }
      } catch {
        // Cookie expired / network down — user lands on /login anyway.
      } finally {
        setIsLoading(false);
      }
    };
    rehydrateSession();
  }, []);

  const login = useCallback(
    (newUser: AuthUser) => {
      setUser(newUser);
      navigate(newUser.role === "admin" ? "/admin" : "/");
    },
    [navigate],
  );

  const logout = useCallback(async () => {
    try {
      await fetch("/api/auth/logout", {
        method: "POST",
        credentials: "include",
      });
    } catch {
      // Logout proceeds locally regardless of the server response.
    } finally {
      setUser(null);
      navigate("/login");
    }
  }, [navigate]);

  return (
    <AuthContext.Provider value={{ user, isLoading, login, logout }}>
      {children}
    </AuthContext.Provider>
  );
};
