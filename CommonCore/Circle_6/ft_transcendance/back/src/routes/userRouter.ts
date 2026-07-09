import express from "express";
import { QueryFailedError } from "typeorm";
import { logger } from "@/logger";
import { deleteUser, findAllUsers, updateUser } from "@/services/userService";
import { repos } from "@/db/repos";
import { deleteSessionTokenCookie, invalidateAllUserSessions } from "@/auth/session";
import { requireRole } from "@/middlewares/authMiddlewares";
import { validate } from "@/middlewares/validate";
import { updateUserSchema, uuidParamSchema } from "@/schemas/user";
import { sendDataDeletionEmail, sendDataExportEmail } from "@/services/emailService";

const router = express.Router();

// Postgres unique-constraint violation (e.g. email already taken).
function isUniqueViolation(error: unknown): boolean {
  return (
    error instanceof QueryFailedError && (error.driverError as { code?: string })?.code === "23505"
  );
}

// Get all users (for admin interface)
router.get("/", requireRole("admin"), async (_, res) => {
  try {
    const users = await findAllUsers();
    res.status(200).json({ success: true, users });
  } catch (error) {
    logger.error(error);
    return res.status(500).json({ success: false, error: "Error." });
  }
});

router.get("/me", async (req, res) => {
  const userId = req.user?.id;
  if (!userId) {
    return res.status(401).json({ success: false, error: "Not authenticated." });
  }

  try {
    const user = await repos.user().findOne({
      where: { id: userId },
      select: ["id", "email", "name", "lastname", "role", "created_at"],
    });
    if (!user) {
      return res.status(404).json({ success: false, error: "User not found." });
    }
    res.status(200).json({ success: true, user });
  } catch (error) {
    logger.error(error);
    return res.status(500).json({ success: false, error: "Error." });
  }
});

// Delete Own Account
router.delete("/me", async (req, res) => {
  const userId = req.user!.id;
  if (!userId) {
    return res.status(401).json({ success: false, error: "Not authenticated." });
  }

  try {
    const user = await repos.user().findOneBy({ id: userId });
    const userEmail = user?.email;

    await repos.user().delete({ id: userId });
    await invalidateAllUserSessions(userId);
    deleteSessionTokenCookie(res);

    if (userEmail) {
      await sendDataDeletionEmail(userEmail);
    }

    // 200 with a body — a 204 silently discards any JSON payload.
    return res.status(200).json({ success: true, message: "Account successfully deleted" });
  } catch (error) {
    logger.error(error, "Account deletion error");
    return res.status(500).json({ success: false, error: "Failed to delete account." });
  }
});

// Export User Data
router.get("/me/export", async (req, res) => {
  const userId = req.user!.id;
  try {
    const [user, sessions, authAttempts] = await Promise.all([
      repos.user().findOneBy({ id: userId }),
      repos.session().find({ where: { userId } }),
      repos.authAttempt().find({ where: { user: { id: userId } } }),
    ]);
    if (!user) {
      return res.status(404).json({ success: false, error: "User not found" });
    }
    const exportData = {
      exported_at: new Date().toISOString(),
      user: {
        id: user.id,
        email: user.email,
        name: user.name,
        lastname: user.lastname,
        role: user.role,
        created_at: user.created_at,
      },
      sessions: sessions.map((s) => ({
        id: s.id,
        created_at: s.createdAt,
        expires_at: s.expiresAt,
      })),
      auth_attempts: authAttempts.map((a) => ({ action: a.action, success: a.success })),
    };

    await sendDataExportEmail(user.email);

    res.status(200).json(exportData);
  } catch (error) {
    logger.error(error, "Data export error");
    return res.status(500).json({ success: false, error: "Failed to export data." });
  }
});

// Edit a user (admin only)
router.put(
  "/:id",
  requireRole("admin"),
  validate(uuidParamSchema, "params"),
  validate(updateUserSchema),
  async (req, res) => {
    const { id } = req.params as { id: string };
    const { email, name, lastname, role } = req.body;
    const userId = req.user?.id;

    if (userId === id && role !== "admin") {
      return res.status(400).json({ success: false, error: "Cannot change your own role." });
    }

    if (role !== undefined && role !== "admin") {
      const target = await repos.user().findOneBy({ id });
      if (target?.role === "admin") {
        const adminCount = await repos.user().countBy({ role: "admin" });
        if (adminCount <= 1) {
          return res
            .status(400)
            .json({ success: false, error: "Cannot demote the last remaining admin." });
        }
      }
    }

    try {
      const updatedUser = await updateUser(id, { email, name, lastname, role });
      if (!updatedUser) {
        return res.status(404).json({ success: false, error: "User not found." });
      }
      res.status(200).json({ success: true, user: updatedUser });
    } catch (error) {
      if (isUniqueViolation(error)) {
        return res.status(409).json({ success: false, error: "Email already in use." });
      }
      logger.error(error, "User update error");
      return res.status(500).json({ success: false, error: "Failed to update user." });
    }
  },
);

// // Update user password (admin only)
// router.put('/users/:id/password', async (req, res) => {
//     const { id } = req.params;
//     const { newPassword, currentUserRole } = req.body;

//     if (currentUserRole !== 'admin') {
//         return res.status(403).json({ success: false, error: 'Unauthorized.' });
//     }

//     try {
//         const hashedPassword = await bcrypt.hash(newPassword, saltRounds);
//         await query('UPDATE users SET password = $1 WHERE id = $2', [hashedPassword, id]);
//         res.status(200).json({ success: true, message: 'Password updated.' });
//     } catch (error) {
//         console.error(error);
//         res.status(500).json({ success: false, error: 'Error.' });
//     }
// });

// Delete a user (admin only)
router.delete(
  "/:id",
  requireRole("admin"),
  validate(uuidParamSchema, "params"),
  async (req, res) => {
    const { id } = req.params as { id: string };
    const userId = req.user?.id;

    if (userId === id) {
      return res.status(400).json({ success: false, error: "Cannot delete your own account." });
    }

    try {
      const deletedUser = await deleteUser(id);
      if (!deletedUser) {
        return res.status(404).json({ success: false, error: "User not found." });
      }
      await sendDataDeletionEmail(deletedUser.email);
      res.status(200).json({ success: true, message: "User deleted." });
    } catch (error) {
      logger.error(error, "User deletion error");
      return res.status(500).json({ success: false, error: "Failed to delete user." });
    }
  },
);

export default router;
