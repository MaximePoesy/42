import { getDataSource } from "@/db";
import { User } from "@/db/models/user";
import { hashPassword } from "@/auth/password";
import { logger } from "@/logger";
import { type Env } from "@/env";

export async function seedAdmin(env: Env): Promise<void> {
  const repo = getDataSource().getRepository(User);

  const existing = await repo.findOneBy({ email: env.ADMIN_EMAIL });
  if (existing) {
    logger.info(`Admin user already exists (${existing.email}), skipping seed.`);
    return;
  }

  const hashedPassword = await hashPassword(env.ADMIN_PASSWORD);
  const admin = repo.create({
    email: env.ADMIN_EMAIL,
    password: hashedPassword,
    name: "Admin",
    lastname: "Admin",
    role: "admin",
  });

  await repo.save(admin);
  logger.info(`Admin user seeded: ${env.ADMIN_EMAIL}`);
}
