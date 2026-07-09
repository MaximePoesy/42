import { z } from "zod";
import { emailSchema, nameSchema } from "./auth";

export const ROLES = ["user", "admin"] as const;
export const roleSchema = z.enum(ROLES);

export const uuidParamSchema = z.object({
  id: z.string().uuid("Invalid user id"),
});

// All fields optional so the admin can patch one field at a time, but every
// provided field is still validated against the same rules as signup.
export const updateUserSchema = z
  .object({
    email: emailSchema.optional(),
    name: nameSchema.optional(),
    lastname: nameSchema.optional(),
    role: roleSchema.optional(),
  })
  .strict()
  .refine((data) => Object.keys(data).length > 0, {
    message: "No fields to update",
  });

export type UpdateUserBody = z.infer<typeof updateUserSchema>;
export type UuidParams = z.infer<typeof uuidParamSchema>;
