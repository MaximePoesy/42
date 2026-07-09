import { getDataSource } from "@/db";
import { User } from "./models/user";
import { Session } from "./models/session";
import { AuthAttempt } from "./models/authAttempt";

export const repos = {
  user: () => getDataSource().getRepository(User),
  session: () => getDataSource().getRepository(Session),
  authAttempt: () => getDataSource().getRepository(AuthAttempt),
};
