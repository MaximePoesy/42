import "reflect-metadata";
import express from "express";
import cors from "cors";
import cookieParser from "cookie-parser";
import z from "zod";
import { loadVaultSecrets } from "./vaultConfig";
import { validateEnv, type Env } from "./env";
import { initDB } from "./db";
import { seedAdmin } from "./db/seed";
import { logger, loggerMiddleware } from "./logger";

import authRouter from "./routes/authRouter";
import userRouter from "./routes/userRouter";
import { requireAuth } from "./middlewares/authMiddlewares";
import { apiLimiter, authLimiter } from "./middlewares/rateLimitMiddlewares";

const app = express();

// One hop in front of us: the Nginx/WAF container forwards X-Forwarded-For.
// Required so express-rate-limit keys off the real client IP, not Nginx's.
app.set("trust proxy", 1);

async function startServer() {
  await loadVaultSecrets();

  let env: Env;
  try {
    env = validateEnv();
  } catch (err) {
    if (err instanceof z.ZodError) {
      const missing = err.issues.map((i) => i.path.join(".")).join(", ");
      logger.error(`Missing or invalid environment variables: ${missing}`);
    } else {
      logger.error(err, "Failed to validate environment: ");
    }
    process.exit(1);
  }

  await initDB(env);
  await seedAdmin(env);

  // Only the WAF TLS ingress is a legitimate browser origin. Reflecting any
  // origin with credentials would let a third-party site send authenticated
  // cross-origin requests.
  app.use(
    cors({
      origin: ["https://localhost:8443"],
      credentials: true,
    }),
  );

  app.use(loggerMiddleware);
  app.use(cookieParser());
  app.use(express.json());

  app.use("/health", (_, res) => res.json({ status: "ok" }));
  app.use("/api", apiLimiter);
  app.use(["/api/auth/login", "/api/auth/signup"], authLimiter);
  app.use("/api/auth", authRouter);
  app.use("/api/users", requireAuth, userRouter);

  app.listen(env.PORT, () => {
    logger.info(`Server is running on http://localhost:${env.PORT}`);
  });
}

startServer().catch((err) => {
  logger.error(err, "Failed to start server:");
});
