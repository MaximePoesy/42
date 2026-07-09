import { logger } from "@/logger";
import { Request, Response, NextFunction } from "express";
import { validateSessionToken } from "@/auth/session";

export async function requireAuth(req: Request, res: Response, next: NextFunction) {
  const token = req.cookies?.session;
  if (!token) {
    return res.status(401).json({ success: false, error: "Not authenticated" });
  }

  try {
    const session = await validateSessionToken(token);
    if (!session) {
      return res.status(401).json({ success: false, error: "Invalid or expired session" });
    }

    req.user = session.user;
    req.session = session.session;
    next();
  } catch (error) {
    logger.error(error, "Session validation error");
    return res.status(500).json({ success: false, error: "Authentication failed" });
  }
}

export function requireRole(...roles: string[]) {
  return (req: Request, res: Response, next: NextFunction) => {
    if (!req.user || !roles.includes(req.user.role)) {
      return res.status(403).json({ success: false, error: "Forbidden" });
    }
    next();
  };
}
