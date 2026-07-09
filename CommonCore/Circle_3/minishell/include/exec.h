/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:40:01 by staverni          #+#    #+#             */
/*   Updated: 2025/05/18 12:20:05 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define NUM_CMD_TYPES 8

typedef struct s_cmd		t_cmd;
typedef struct s_execcmd	t_execcmd;
typedef enum e_cmdtype		t_cmd_type;
typedef struct s_shell		t_shell;

typedef enum e_filemask
{
	FD_IN = O_RDONLY,
	FD_OUT = O_WRONLY | O_CREAT | O_TRUNC,
	FD_APPEND = O_WRONLY | O_CREAT | O_APPEND,
	FD_HEREDOC = O_RDONLY | O_CREAT | O_TRUNC
}							t_filemask;

/********************************* EXECUTION **********************************/

typedef int					(*t_cmd_handler)(t_shell *sh, t_cmd *cmd);

int							execution(t_shell *sh, t_cmd *cmd);
int							exec_builtin(t_shell *sh, t_cmd *cmd);
int							exec_cmd(t_shell *sh, t_cmd *cmd);
int							exec_pipe(t_shell *sh, t_cmd *cmd);
int							exec_redir_in(t_shell *sh, t_cmd *cmd);
int							exec_redir_out(t_shell *sh, t_cmd *cmd);
int							exec_redir_append(t_shell *sh, t_cmd *cmd);
int							exec_redir_heredoc(t_shell *sh, t_cmd *cmd);

/*********************************** UTILS ************************************/

int							cmd_in_parent(char *path);

/********************************* BUILTINS ***********************************/

int							builtin_echo(t_execcmd *cmd);
int							builtin_cd(t_execcmd *cmd, t_list **env);
int							builtin_pwd(void);
int							builtin_export(t_execcmd *cmd, t_list **env);
void						handle_export_arg(char *arg, t_list **env);
int							builtin_unset(t_execcmd *cmd, t_list **env);
int							builtin_env(t_list *env);
int							builtin_exit(t_shell *sh);

#endif
