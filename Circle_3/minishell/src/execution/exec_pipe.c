/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:22 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/18 10:17:11 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_left(t_shell *sh, t_cmd *cmd, pid_t *pid, int *fd)
{
	int	exit_status;

	*pid = fork();
	if (*pid < 0)
	{
		print_error_null("error: fork");
		return (1);
	}
	if (*pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			print_error_null("error: child process");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
		exit_status = execution(sh, cmd);
		exit_shell(sh, exit_status);
	}
	return (0);
}

static int	pipe_right(t_shell *sh, t_cmd *cmd, pid_t *pid, int *fd)
{
	int	exit_status;

	*pid = fork();
	if (*pid < 0)
	{
		print_error_null("error: fork");
		return (1);
	}
	if (*pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			print_error_null("error: child process");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
		exit_status = execution(sh, cmd);
		exit_shell(sh, exit_status);
	}
	return (0);
}

int	handle_pipe(t_shell *sh, t_cmd *cmd, pid_t *pids, int *fd)
{
	if (pipe_left(sh, cmd->u.pipe.left, &pids[0], fd))
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pipe_right(sh, cmd->u.pipe.right, &pids[1], fd))
	{
		close(fd[0]);
		close(fd[1]);
		if (pids[0] > 0)
		{
			kill(pids[0], SIGKILL);
			waitpid(pids[0], NULL, 0);
		}
		return (1);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	finish_pipeline(pid_t *pids, int *exit_status)
{
	int	final_status;

	final_status = 0;
	if (pids[0] > 0)
		waitpid(pids[0], &exit_status[0], 0);
	if (pids[1] > 0)
	{
		waitpid(pids[1], &exit_status[1], 0);
		if (WIFEXITED(exit_status[1]))
			final_status = WEXITSTATUS(exit_status[1]);
		else if (WIFSIGNALED(exit_status[1]))
			final_status = 128 + WTERMSIG(exit_status[1]);
	}
	return (final_status);
}

int	exec_pipe(t_shell *sh, t_cmd *cmd)
{
	int		fd[2];
	int		exit_status[2];
	int		status;
	pid_t	pids[2];

	pids[0] = -1;
	pids[1] = -1;
	if (pipe(fd) == -1)
	{
		print_error_null("error: pipe");
		return (1);
	}
	if (handle_pipe(sh, cmd, pids, fd))
		return (1);
	status = finish_pipeline(pids, exit_status);
	return (status);
}
