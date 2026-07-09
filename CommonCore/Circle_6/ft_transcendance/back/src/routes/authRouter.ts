import express from "express";
import { findUserByEmail, findUserByEmailWithPassword, createUser } from "@/services/userService";
import { hashPassword, verifyPasswordHash } from "@/auth/password";
import {
  createSession,
  invalidateSession,
  validateSessionToken,
  setSessionTokenCookie,
  deleteSessionTokenCookie,
} from "@/auth/session";
import { getDataSource } from "@/db";
import { AuthAttempt } from "@/db/models/authAttempt";
import { logger } from "@/logger";
import { validate } from "@/middlewares/validate";
import { requireAuth } from "@/middlewares/authMiddlewares";
import { loginSchema, signupSchema } from "@/schemas/auth";

const router = express.Router();

function attemptRepo() {
  return getDataSource().getRepository(AuthAttempt);
}

async function logAttempt(
  email: string,
  action: "LOGIN" | "SIGNUP",
  success: boolean,
  user?: { id: string } | null,
) {
  const attempt = attemptRepo().create({ email, action, success, user: user ?? undefined });
  await attemptRepo().save(attempt);
}

// POST /api/auth/signup
router.post("/signup", validate(signupSchema), async (req, res) => {
  const { email, password, name, lastname } = req.body;

  try {
    const existing = await findUserByEmail(email);
    if (existing) {
      await logAttempt(email, "SIGNUP", false);
      return res.status(409).json({ success: false, error: "Email already in use" });
    }

    const hashedPassword = await hashPassword(password);
    const user = await createUser({
      email,
      password: hashedPassword,
      name,
      lastname,
      role: "user",
    });

    await logAttempt(email, "SIGNUP", true, user);

    const { token, expiresAt } = await createSession(user.id);
    setSessionTokenCookie(res, token, expiresAt);

    const { password: _, ...safe } = user;
    return res.status(201).json({ success: true, user: safe });
  } catch (error) {
    logger.error(error, "Signup error");
    await logAttempt(email, "SIGNUP", false).catch(() => {});
    return res.status(500).json({ success: false, error: "Signup failed" });
  }
});

// POST /api/auth/login
router.post("/login", validate(loginSchema), async (req, res) => {
  const { email, password } = req.body;

  try {
    const user = await findUserByEmailWithPassword(email);
    if (!user) {
      await logAttempt(email, "LOGIN", false);
      return res.status(401).json({ success: false, error: "Authentication failed." });
    }

    const valid = await verifyPasswordHash(user.password, password);
    if (!valid) {
      await logAttempt(email, "LOGIN", false, user);
      return res.status(401).json({ success: false, error: "Authentication failed." });
    }

    await logAttempt(email, "LOGIN", true, user);

    const { token, expiresAt } = await createSession(user.id);
    setSessionTokenCookie(res, token, expiresAt);

    const { password: _, ...safe } = user;
    return res.status(200).json({ success: true, user: safe });
  } catch (error) {
    logger.error(error, "Login error");
    return res.status(500).json({ success: false, error: "Login failed." });
  }
});

// GET /api/auth/session
// Silent session probe for the front's boot-time rehydration. Always answers
// 200 (user: null when anonymous) so the browser console stays free of 401s
// on logged-out page loads — the subject requires a clean console.
router.get("/session", async (req, res) => {
  const token = req.cookies?.session;
  if (!token) {
    return res.status(200).json({ success: true, user: null });
  }

  try {
    const result = await validateSessionToken(token);
    if (!result) {
      return res.status(200).json({ success: true, user: null });
    }
    const { password: _, ...safe } = result.user;
    return res.status(200).json({ success: true, user: safe });
  } catch (error) {
    logger.error(error, "Session probe error");
    return res.status(200).json({ success: true, user: null });
  }
});

// GET /api/auth/verify
// Session probe used by the WAF's auth_request to gate /ai/* endpoints:
// nginx forwards the client's cookie here and only proxies to the AI engine
// when this answers 2xx.
router.get("/verify", requireAuth, (_req, res) => {
  return res.status(204).end();
});

// POST /api/auth/logout
router.post("/logout", async (req, res) => {
  const token = req.cookies?.session;
  if (!token) {
    return res.status(401).json({ success: false, error: "Not authenticated." });
  }

  try {
    const result = await validateSessionToken(token);
    if (!result) {
      deleteSessionTokenCookie(res);
      return res.status(401).json({ success: false, error: "Invalid or expired session." });
    }

    await invalidateSession(result.session.id);
    deleteSessionTokenCookie(res);
    return res.status(200).json({ success: true });
  } catch (error) {
    logger.error(error, "Logout error");
    return res.status(500).json({ success: false, error: "Logout failed." });
  }
});

// Update user password (admin only)
// router.put('/reset/:id', async (req, res) => {
//     const { id } = req.params;
//     const { newPassword, currentUserRole } = req.body;

//     if (currentUserRole !== 'admin') {
//         return res.status(403).json({ success: false, error: 'Unauthorized.' });
//     }

//     try {
//         const hashedPassword = await bcrypt.hash(newPassword, saltRounds);
//         await query('UPDATE users SET password = $1 WHERE id = $2', [hashedPassword, id]);
//         res.status(200).json({ success: true, message: 'Password updated.' });
//     } catch (error) {
//         console.error(error);
//         res.status(500).json({ success: false, error: 'Error.' });
//     }
// });

export default router;
