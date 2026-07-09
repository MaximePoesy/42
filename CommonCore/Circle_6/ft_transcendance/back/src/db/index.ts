import { DataSource } from "typeorm";
import models from "@/db/models/index";
import { Env } from "@/env";
import { logger } from "@/logger";

let dataSource: DataSource | null = null;

export async function initDB(env: Env): Promise<DataSource> {
  if (dataSource) return dataSource;

  dataSource = new DataSource({
    type: "postgres",
    host: env.DB_HOST,
    port: env.DB_PORT,
    username: env.DB_USER,
    password: env.DB_PASSWORD,
    database: env.DB_NAME,
    entities: Object.values(models),
    synchronize: true,
    logging: false,
  });

  await dataSource.initialize();
  logger.info("Data Source has been initialized!");
  return dataSource;
}

export function getDataSource(): DataSource {
  if (!dataSource) {
    throw new Error("Database not initialized. Call initDB() first.");
  }
  return dataSource;
}
