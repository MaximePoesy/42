import type { User } from "@/db/models/user";

// The one client-facing shape of a user. Deliberately NO password field.
// DB column `created_at` becomes `registerDate` (the name the admin UI expects).
export interface PublicUser {
  id: string;
  email: string;
  name: string;
  lastname: string;
  role: string;
  registerDate: Date;
}

export function toPublicUser(user: User): PublicUser {
  return {
    id: user.id,
    email: user.email,
    name: user.name,
    lastname: user.lastname,
    role: user.role,
    registerDate: user.created_at,
  };
}
