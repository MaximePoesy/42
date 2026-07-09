// Mirror of the backend Zod rules in back/src/schemas/auth.ts.
// Keep these aligned — backend remains the source of truth for security.

export const EMAIL_MAX = 254;
export const PASSWORD_MIN = 8;
export const PASSWORD_MAX = 128;
export const NAME_MAX = 100;

// RFC-5322-lite: good enough to catch typos; the backend re-validates.
const EMAIL_RE = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

export type FieldErrors = {
  email?: string;
  password?: string;
  name?: string;
  lastname?: string;
};

export interface SignupInput {
  email: string;
  password: string;
  name: string;
  lastname: string;
}

export interface LoginInput {
  email: string;
  password: string;
}

function validateEmail(email: string): string | undefined {
  const trimmed = email.trim();
  if (trimmed.length < 3) return "Email is too short";
  if (trimmed.length > EMAIL_MAX) return "Email is too long";
  if (!EMAIL_RE.test(trimmed)) return "Invalid email address";
  return undefined;
}

function validateName(value: string, field: "name" | "lastname"): string | undefined {
  const trimmed = value.trim();
  if (trimmed.length < 1) return field === "name" ? "Name is required" : "Last name is required";
  if (trimmed.length > NAME_MAX)
    return field === "name" ? "Name is too long" : "Last name is too long";
  return undefined;
}

export function validateLogin(input: LoginInput): FieldErrors {
  const errors: FieldErrors = {};
  const emailErr = validateEmail(input.email);
  if (emailErr) errors.email = emailErr;
  if (!input.password) errors.password = "Password is required";
  else if (input.password.length > PASSWORD_MAX) errors.password = "Password is too long";
  return errors;
}

export function validateSignup(input: SignupInput): FieldErrors {
  const errors: FieldErrors = {};
  const emailErr = validateEmail(input.email);
  if (emailErr) errors.email = emailErr;

  if (input.password.length < PASSWORD_MIN) {
    errors.password = `Password must be at least ${PASSWORD_MIN} characters`;
  } else if (input.password.length > PASSWORD_MAX) {
    errors.password = "Password is too long";
  }

  const nameErr = validateName(input.name, "name");
  if (nameErr) errors.name = nameErr;
  const lastnameErr = validateName(input.lastname, "lastname");
  if (lastnameErr) errors.lastname = lastnameErr;

  return errors;
}

export function hasErrors(errors: FieldErrors): boolean {
  return Object.values(errors).some(Boolean);
}

export function firstError(errors: FieldErrors): string | undefined {
  return Object.values(errors).find(Boolean);
}
