/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:27 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/18 10:20:51 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_handler	get_command_handler(t_cmd *cmd, t_cmdtype type)
{
	if (type == CMD)
	{
		if (is_builtin(cmd->u.exec.argv[0]))
			return (exec_builtin);
		else
			return (exec_cmd);
	}
	else if (type == PIPE)
		return (exec_pipe);
	else if (type == REDIR_IN)
		return (exec_redir_in);
	else if (type == REDIR_OUT)
		return (exec_redir_out);
	else if (type == REDIR_APPEND)
		return (exec_redir_append);
	else if (type == REDIR_HEREDOC)
		return (exec_redir_heredoc);
	else
		return (NULL);
}

int	execution(t_shell *sh, t_cmd *cmd)
{
	t_cmd_handler	handler;

	if (!cmd)
		return (0);
	handler = get_command_handler(cmd, cmd->type);
	if (cmd->type < 0 || cmd->type >= NUM_CMD_TYPES || !handler)
		return (print_error_null("Invalid command type"), 1);
	return (handler(sh, cmd));
}
