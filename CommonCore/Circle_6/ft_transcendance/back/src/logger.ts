import pino from "pino";
import pinoHttp from "pino-http";

// pino-pretty is a devDependency: the production image (npm ci --omit=dev)
// doesn't ship it, and JSON logs on stdout are what Docker expects anyway.
export const logger = pino({
  level: process.env.LOG_LEVEL || "info",
  ...(process.env.NODE_ENV !== "production" && {
    transport: {
      target: "pino-pretty",
      options: { colorize: true },
    },
  }),
});

export const loggerMiddleware = pinoHttp({ logger });
