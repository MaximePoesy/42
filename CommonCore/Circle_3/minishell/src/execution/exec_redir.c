/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:24 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/19 10:57:55 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redir_in(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*r;
	int			fd;

	r = &cmd->u.redir;
	fd = open(r->file, O_RDONLY);
	if (fd < 0)
	{
		perror("open for input");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 stdin");
		close(fd);
		return (1);
	}
	close(fd);
	return (execution(sh, r->cmd));
}

int	exec_redir_out(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*r;
	int			fd;

	r = &cmd->u.redir;
	fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("minishell: open");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (execution(sh, r->cmd));
}

static int	setup_append_redir(const char *filename, int *saved_stdout)
{
	int	fd;

	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout < 0)
	{
		perror("minishell: dup");
		return (-1);
	}
	fd = open(filename, FD_APPEND, 0644);
	if (fd < 0)
	{
		perror("open for append");
		close(*saved_stdout);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 stdout");
		close(fd);
		close(*saved_stdout);
		return (-1);
	}
	close(fd);
	return (0);
}

int	exec_redir_append(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*r;
	int			saved_stdout;

	r = &cmd->u.redir;
	if (setup_append_redir(r->file, &saved_stdout) < 0)
		return (1);
	return (execution(sh, r->cmd));
}
