import "reflect-metadata";
import { Entity, PrimaryGeneratedColumn, Column, CreateDateColumn, ManyToOne } from "typeorm";
import { User } from "@/db/models/user";

@Entity("auth_attempts")
export class AuthAttempt {
  @PrimaryGeneratedColumn({ type: "int" })
  id: number;

  @Column({ type: "varchar" })
  email: string;

  @Column({ type: "varchar" })
  action: "LOGIN" | "SIGNUP";

  @Column({ type: "boolean" })
  success: boolean;

  @CreateDateColumn({ type: "timestamp" })
  timestamp: Date;

  @ManyToOne(() => User, { nullable: true, onDelete: "SET NULL" })
  user: User;
}
