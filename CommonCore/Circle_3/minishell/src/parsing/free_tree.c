/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:37:20 by staverni          #+#    #+#             */
/*   Updated: 2025/05/15 16:24:48 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_node(t_cmdtype type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND
		|| type == REDIR_HEREDOC);
}

void	free_cmd_tree(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->type == CMD)
	{
		i = 0;
		while (cmd->u.exec.argv[i])
		{
			free(cmd->u.exec.argv[i]);
			i++;
		}
		free(cmd->u.exec.path);
	}
	else if (cmd->type == PIPE)
	{
		free_cmd_tree(cmd->u.pipe.left);
		free_cmd_tree(cmd->u.pipe.right);
	}
	else if (is_redir_node(cmd->type))
	{
		free(cmd->u.redir.file);
		free_cmd_tree(cmd->u.redir.cmd);
	}
	free(cmd);
}
