import crypto from "node:crypto";

export function generateSecureRandomString(): string {
  return crypto.randomBytes(24).toString("base64url");
}

export function hashSecret(secret: string): Uint8Array {
  return crypto.createHash("sha256").update(secret).digest();
}

export function constantTimeEqual(a: Uint8Array, b: Uint8Array): boolean {
  if (a.length !== b.length) return false;
  return crypto.timingSafeEqual(a, b);
}
