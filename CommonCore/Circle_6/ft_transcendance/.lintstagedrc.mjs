// Lint-staged runs commands on files staged for commit.
// - Prettier runs from root for all formattable files (config is shared).
// - ESLint runs per-project via `npm --prefix` so CWD matches the flat-config
//   location (required by ESLint flat config). The `lint:files` script in each
//   project's package.json is `eslint --fix --no-warn-ignored`, and lint-staged
//   appends the (project-relative) file paths after `--`.
import path from "node:path";

const eslintIn = (project) => (files) => {
  const projectDir = path.resolve(project);
  const rel = files.map((f) => path.relative(projectDir, path.resolve(f)));
  return `npm run lint:files --prefix ${project} -- ${rel.join(" ")}`;
};

export default {
  // Prettier: format everything Prettier knows.
  "*.{js,jsx,ts,tsx,json,css,md,yml,yaml,html}": "prettier --write",

  // ESLint per project — paths get rewritten to be project-relative.
  "front/**/*.{ts,tsx}": eslintIn("front"),
  "back/**/*.ts": eslintIn("back"),
};
