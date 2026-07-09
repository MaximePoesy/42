import type { Response } from "express";
import { getDataSource } from "@/db";
import { Session } from "@/db/models/session";
import { User } from "@/db/models/user";
import { generateSecureRandomString, hashSecret, constantTimeEqual } from "./crypto";

const SESSION_DURATION_MS = 1000 * 60 * 60 * 24; // 1 day

export async function createSession(userId: string): Promise<{ token: string; expiresAt: Date }> {
  const id = generateSecureRandomString();
  const secret = generateSecureRandomString();
  const secretHash = hashSecret(secret);

  const session = new Session();
  session.id = id;
  session.secretHash = secretHash;
  session.userId = userId;
  session.expiresAt = new Date(Date.now() + SESSION_DURATION_MS);

  await getDataSource().getRepository(Session).save(session);

  return { token: `${id}.${secret}`, expiresAt: session.expiresAt };
}

export async function validateSessionToken(
  token: string,
): Promise<{ user: User; session: Session } | null> {
  const parts = token.split(".");
  if (parts.length !== 2) return null;
  const [sessionId, sessionSecret] = parts;
  const db = getDataSource();
  const sessionRepo = db.getRepository(Session);
  const session = await sessionRepo.findOne({
    where: { id: sessionId },
    relations: ["user"],
  });
  if (!session) return null;
  // Check expiration
  if (new Date() > session.expiresAt) {
    await sessionRepo.remove(session);
    return null;
  }
  // Verify secret
  const providedHash = hashSecret(sessionSecret);
  if (!constantTimeEqual(providedHash, session.secretHash)) {
    return null;
  }
  return { user: session.user, session };
}

export async function invalidateSession(sessionId: string): Promise<void> {
  await getDataSource().getRepository(Session).delete(sessionId);
}

export async function invalidateAllUserSessions(userId: string): Promise<void> {
  await getDataSource().getRepository(Session).delete({ userId });
}

export function setSessionTokenCookie(res: Response, token: string, expiresAt: Date): void {
  res.cookie("session", token, {
    httpOnly: true,
    path: "/",
    secure: true,
    sameSite: "lax",
    expires: expiresAt,
  });
}

export function deleteSessionTokenCookie(res: Response): void {
  res.clearCookie("session", { path: "/" });
}
