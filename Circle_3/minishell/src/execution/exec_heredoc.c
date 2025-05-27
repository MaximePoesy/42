/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:00:44 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/18 11:01:34 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_write(int write_fd, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			return (0);
		}
		dprintf(write_fd, "%s\n", line);
		free(line);
	}
}

int	exec_redir_heredoc(t_shell *sh, t_cmd *cmd)
{
	int			pipefd[2];
	t_redircmd	*r;

	(void)sh;
	r = &cmd->u.redir;
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (1);
	}
	heredoc_write(pipefd[1], r->file);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		close(pipefd[0]);
		return (1);
	}
	close(pipefd[0]);
	return (execution(sh, r->cmd));
}
