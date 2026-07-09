import "reflect-metadata";
import { Entity, PrimaryColumn, Column, CreateDateColumn, OneToMany, BeforeInsert } from "typeorm";
import { uuidv7 } from "uuidv7";
import { AuthAttempt } from "./authAttempt";
import { Session } from "./session";

@Entity("users")
export class User {
  @PrimaryColumn({ type: "uuid" })
  id: string;

  @Column({ type: "varchar", unique: true })
  email: string;

  @Column({ type: "varchar" })
  password: string;

  @Column({ type: "varchar" })
  name: string;

  @Column({ type: "varchar" })
  lastname: string;

  @Column({ type: "varchar" })
  role: string;

  @CreateDateColumn({ name: "created_at" })
  created_at: Date;

  @OneToMany(() => AuthAttempt, (attempt) => attempt.user)
  authAttempts: AuthAttempt[];

  @OneToMany(() => Session, (session) => session.user)
  sessions: Session[];

  @BeforeInsert()
  generateId() {
    this.id = uuidv7();
  }
}
