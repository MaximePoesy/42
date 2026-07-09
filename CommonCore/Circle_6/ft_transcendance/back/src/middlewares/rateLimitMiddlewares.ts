import { rateLimit, ipKeyGenerator } from "express-rate-limit";
import type { Request } from "express";

const TOO_MANY = (action: string) => ({
  success: false,
  error: `Too many ${action}. Please try again later.`,
});

// Broad per-IP limit on all /api/* traffic — defense in depth.
export const apiLimiter = rateLimit({
  windowMs: 15 * 60 * 1000,
  limit: 200,
  standardHeaders: "draft-7",
  legacyHeaders: false,
  message: TOO_MANY("requests"),
});

// Strict per-IP limit on auth endpoints — anti-brute-force on credentials.
// Successful logins do not count toward the quota.
export const authLimiter = rateLimit({
  windowMs: 15 * 60 * 1000,
  limit: 10,
  standardHeaders: "draft-7",
  legacyHeaders: false,
  skipSuccessfulRequests: true,
  keyGenerator: (req: Request) => {
    const email = typeof req.body?.email === "string" ? req.body.email.toLowerCase() : "";
    return `${ipKeyGenerator(req.ip ?? "")}:${email}`;
  },
  message: TOO_MANY("authentication attempts"),
});
