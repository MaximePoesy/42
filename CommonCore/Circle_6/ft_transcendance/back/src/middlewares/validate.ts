import { Request, Response, NextFunction } from "express";
import { ZodError, ZodSchema } from "zod";

type Source = "body" | "params" | "query";

function formatZodError(err: ZodError) {
  return err.issues.map((i) => ({
    path: i.path.join("."),
    message: i.message,
  }));
}

/**
 * Validate one part of the request against a Zod schema.
 * On success the parsed (and coerced/trimmed) value replaces the original on req[source].
 */
export function validate(schema: ZodSchema, source: Source = "body") {
  return (req: Request, res: Response, next: NextFunction) => {
    const result = schema.safeParse(req[source]);
    if (!result.success) {
      return res.status(400).json({
        success: false,
        error: "Validation failed",
        details: formatZodError(result.error),
      });
    }
    // Replace with the parsed value so downstream handlers see normalised data
    // (lowercased emails, trimmed names, coerced types).
    Object.defineProperty(req, source, { value: result.data, writable: true });
    next();
  };
}
