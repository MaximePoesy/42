import z from "zod";
import dotenv from "dotenv";

dotenv.config();

const MAX_PORT = 65_535;

const createPortSchema = ({ defaultPort }: { defaultPort: number }) =>
  z.coerce.number().int().min(0).max(MAX_PORT).optional().default(defaultPort);

const envSchema = z.object({
  PORT: createPortSchema({ defaultPort: 3001 }),
  DB_USER: z.string(),
  DB_PASSWORD: z.string(),
  DB_HOST: z.string(),
  DB_NAME: z.string(),
  DB_PORT: createPortSchema({ defaultPort: 5432 }),
  ADMIN_EMAIL: z.string().email(),
  ADMIN_PASSWORD: z.string(),
});

export function validateEnv() {
  return envSchema.parse(process.env);
}

export type Env = z.infer<typeof envSchema>;
