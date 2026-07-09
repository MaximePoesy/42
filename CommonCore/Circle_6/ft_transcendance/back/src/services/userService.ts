import { getDataSource } from "@/db/index";
import { User } from "@/db/models/user";
import { toPublicUser, type PublicUser } from "./userMapper";

function repo() {
  return getDataSource().getRepository(User);
}

export async function findAllUsers(): Promise<PublicUser[]> {
  // `select` = the password hash is never even fetched from the database.
  const users = await repo().find({
    select: { id: true, email: true, name: true, lastname: true, role: true, created_at: true },
  });
  return users.map(toPublicUser);
}

export async function findUserById(id: string) {
  return repo().findOneBy({ id });
}

export async function findUserByEmail(email: string) {
  return repo().findOne({
    where: { email },
    select: { id: true, email: true, name: true, lastname: true, role: true, created_at: true },
  });
}

export async function findUserByEmailWithPassword(email: string) {
  return repo().findOneBy({ email });
}

export async function createUser(data: Partial<User>) {
  return repo().save(repo().create(data));
}

export async function updateUser(id: string, data: Partial<User>): Promise<PublicUser | null> {
  const user = await findUserById(id);
  if (!user) return null;
  Object.assign(user, data);
  const saved = await repo().save(user);
  // Return the safe shape, never the raw entity (which carries the hash).
  return toPublicUser(saved);
}

export async function deleteUser(id: string) {
  const user = await findUserById(id);
  if (!user) return null;
  return repo().remove(user);
}
