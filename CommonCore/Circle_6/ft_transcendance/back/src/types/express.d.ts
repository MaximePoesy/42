import { Session } from "@/db/models/session";
import { User } from "@/db/models/user";

declare module "express-serve-static-core" {
  interface Request {
    user?: User;
    session?: Session;
  }
}
