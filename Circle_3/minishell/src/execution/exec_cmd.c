/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/18 12:46:20 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_signal_message(int sig)
{
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault\n", 2);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
	else if (sig == SIGABRT)
		ft_putstr_fd("Aborted\n", 2);
	else if (sig == SIGKILL)
		ft_putstr_fd("Killed\n", 2);
	else if (sig == SIGFPE)
		ft_putstr_fd("Floating point exception\n", 2);
	else if (sig == SIGBUS)
		ft_putstr_fd("Bus error\n", 2);
	else if (sig == SIGTERM)
		ft_putstr_fd("Terminated\n", 2);
	else if (sig == SIGILL)
		ft_putstr_fd("Illegal instruction\n", 2);
	else if (sig == SIGPIPE)
		ft_putstr_fd("Broken pipe\n", 2);
	else
		ft_putstr_fd("\n", 2);
}

static int	wait_child(pid_t pid)
{
	int	status;
	int	exit_code;

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		exit_code = WTERMSIG(status);
		print_signal_message(exit_code);
		return (128 + exit_code);
	}
	return (1);
}

static void	do_exec(t_shell *sh, t_execcmd *cmd, t_list *env)
{
	char	**envp;

	envp = list_to_envp(env);
	reset_signals();
	if (!envp)
	{
		perror("malloc");
		exit_shell(sh, 1);
	}
	if (execve((cmd->path), cmd->argv, envp) == -1)
	{
		write(2, "minishell: ", 11);
		perror(cmd->argv[0]);
		free(envp);
		exit_shell(sh, 127);
	}
}

static int	run_external_cmd(t_shell *sh, t_execcmd *exec_cmd)
{
	pid_t	pid;
	int		child_status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		do_exec(sh, exec_cmd, sh->env);
	child_status = wait_child(pid);
	return (child_status);
}

int	exec_cmd(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*exec_cmd;

	exec_cmd = &cmd->u.exec;
	if (!exec_cmd || !exec_cmd->argv[0] || !exec_cmd->path)
		return (0);
	if (is_builtin(exec_cmd->path))
		return (exec_builtin(sh, cmd));
	else if (!ft_strchr(exec_cmd->path, '/'))
		return (exec_error(exec_cmd->path), 127);
	else
		return (run_external_cmd(sh, exec_cmd));
}
