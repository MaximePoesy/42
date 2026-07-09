import { getDataSource } from "@/db";
import { User } from "@/db/models/user";

export async function getUserPasswordHash(userId: string): Promise<string | null> {
  const db = getDataSource();
  const userRepo = db.getRepository(User);
  const user = await userRepo.findOneBy({ id: userId });
  return user ? user.password : null;
}
