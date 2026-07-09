import nodemailer from "nodemailer";
import { logger } from "@/logger";

let transporter: nodemailer.Transporter | undefined;

// Initialize Ethereal transporter dynamically to ensure it works out of the box
nodemailer.createTestAccount().then((testAccount) => {
  transporter = nodemailer.createTransport({
    host: process.env.SMTP_HOST || "smtp.ethereal.email",
    port: parseInt(process.env.SMTP_PORT || "587", 10),
    secure: false, // true for 465, false for other ports
    auth: {
      user: process.env.SMTP_USER && process.env.SMTP_USER !== "test_user@ethereal.email" ? process.env.SMTP_USER : testAccount.user,
      pass: process.env.SMTP_PASS && process.env.SMTP_PASS !== "test_password" ? process.env.SMTP_PASS : testAccount.pass,
    },
  });
}).catch(err => {
  logger.error(`Failed to create Ethereal test account: ${err}`);
});

export const sendDataExportEmail = async (userEmail: string) => {
  if (!transporter) {
    logger.warn(`Mail transporter not ready; skipping export email to ${userEmail}`);
    return;
  }
  try {
    const info = await transporter.sendMail({
      from: process.env.SMTP_FROM || "ft_transcendance <noreply@ft-transcendance.42>",
      to: userEmail,
      subject: "Your Data Export Request",
      text: "You have successfully requested an export of your personal data. Please find it downloaded in your session.",
    });
    logger.info(`Export Email sent to ${userEmail}. Preview URL: ${nodemailer.getTestMessageUrl(info)}`);
  } catch (error) {
    logger.error(`Failed to send data export email to ${userEmail}: ${error}`);
  }
};

export const sendDataDeletionEmail = async (userEmail: string) => {
  if (!transporter) {
    logger.warn(`Mail transporter not ready; skipping deletion email to ${userEmail}`);
    return;
  }
  try {
    const info = await transporter.sendMail({
      from: process.env.SMTP_FROM || "ft_transcendance <noreply@ft-transcendance.42>",
      to: userEmail,
      subject: "Account Deletion Confirmation",
      text: "Your account and all associated personal data have been permanently deleted from our systems.",
    });
    logger.info(`Deletion Email sent to ${userEmail}. Preview URL: ${nodemailer.getTestMessageUrl(info)}`);
  } catch (error) {
    logger.error(`Failed to send data deletion email to ${userEmail}: ${error}`);
  }
};
