/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:05:16 by staverni          #+#    #+#             */
/*   Updated: 2025/05/19 10:55:29 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child_builtin(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*exec_cmd;
	int			status;

	exec_cmd = &cmd->u.exec;
	status = 0;
	if (ft_strcmp(exec_cmd->path, "echo") == 0)
		status = builtin_echo(exec_cmd);
	else if (ft_strcmp(exec_cmd->path, "pwd") == 0)
		status = builtin_pwd();
	else if (ft_strcmp(exec_cmd->path, "env") == 0)
		status = builtin_env(sh->env);
	exit_shell(sh, status);
}

static int	fork_builtin(t_shell *sh, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		print_error_null("error: fork");
		return (1);
	}
	else if (pid == 0)
		exec_child_builtin(sh, cmd);
	waitpid(pid, &status, 0);
	return (status);
}

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*exec_cmd;

	exec_cmd = &cmd->u.exec;
	if (!exec_cmd || !exec_cmd->path)
		return (0);
	if (!cmd_in_parent(exec_cmd->path))
		return (fork_builtin(sh, cmd));
	if (ft_strcmp(exec_cmd->path, "cd") == 0)
		return (builtin_cd(exec_cmd, &sh->env));
	else if (ft_strcmp(exec_cmd->path, "exit") == 0)
		return (builtin_exit(sh));
	else if (ft_strcmp(exec_cmd->path, "export") == 0)
		return (builtin_export(exec_cmd, &sh->env));
	else if (ft_strcmp(exec_cmd->path, "unset") == 0)
		return (builtin_unset(exec_cmd, &sh->env));
	return (0);
}
