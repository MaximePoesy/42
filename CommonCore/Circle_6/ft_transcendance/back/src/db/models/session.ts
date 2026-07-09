import "reflect-metadata";
import { Entity, PrimaryColumn, Column, CreateDateColumn, ManyToOne } from "typeorm";
import { User } from "./user";

@Entity("sessions")
export class Session {
  @PrimaryColumn({ type: "varchar" })
  id: string;

  @Column({ type: "bytea" })
  secretHash: Uint8Array;

  @Column({ type: "uuid" })
  userId: string;

  @Column({ type: "timestamptz" })
  expiresAt: Date;

  @CreateDateColumn({ type: "timestamptz" })
  createdAt: Date;

  @ManyToOne(() => User, { onDelete: "CASCADE" })
  user: User;
}
