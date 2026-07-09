import fs from "node:fs";
import vault from "node-vault";

import { logger } from "./logger";

const VAULT_ADDR = process.env.VAULT_ADDR || "http://ft_vault:8200";
const VAULT_SECRET_PATH = "secret/data/ft_transcendance/back";

export async function loadVaultSecrets(): Promise<void> {
  const roleIdFile = process.env.VAULT_ROLE_ID_FILE;
  const secretIdFile = process.env.VAULT_SECRET_ID_FILE;

  if (!roleIdFile || !secretIdFile) {
    logger.warn("VAULT_ROLE_ID_FILE or VAULT_SECRET_ID_FILE not set, skipping Vault.");
    return;
  }

  let roleId: string;
  let secretId: string;

  try {
    roleId = fs.readFileSync(roleIdFile, "utf-8").trim();
    secretId = fs.readFileSync(secretIdFile, "utf-8").trim();
  } catch {
    logger.warn("Could not read AppRole credential files, skipping Vault.");
    return;
  }

  if (!roleId || !secretId) {
    logger.warn("AppRole credentials are empty, skipping Vault.");
    return;
  }

  try {
    const client = vault({ endpoint: VAULT_ADDR });

    const auth = await client.approleLogin({ role_id: roleId, secret_id: secretId });
    client.token = auth.auth.client_token;

    const result = await client.read(VAULT_SECRET_PATH);
    const data = result.data.data;

    process.env.DB_USER = data.user;
    process.env.DB_PASSWORD = data.password;
    process.env.DB_NAME = data.name;
    process.env.DB_HOST = data.host;
    process.env.DB_PORT = data.port;
    process.env.ADMIN_EMAIL = data.admin_email;
    process.env.ADMIN_PASSWORD = data.admin_password;

    logger.info(`Secrets loaded from Vault (${VAULT_ADDR})`);
  } catch (error) {
    logger.warn("Could not load secrets from Vault, falling back to environment variables.");
    logger.debug(`Vault error: ${error instanceof Error ? error.message : String(error)}`);
  }
}
