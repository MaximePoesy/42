/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:09:05 by staverni          #+#    #+#             */
/*   Updated: 2025/05/05 22:00:16 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exec_argv(t_execcmd *cmd)
{
	int	i;

	if (!cmd || (cmd->argv) == NULL)
		return ;
	i = 0;
	while (i < cmd->argc)
	{
		free(cmd->argv[i]);
		i++;
	}
}

t_cmd	*set_exec_node(t_execcmd *cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (print_error_null("Memory allocation error"));
	node->type = CMD;
	node->u.exec = *cmd;
	node->u.exec.path = NULL;
	return (node);
}

t_cmd	*parse_exec(t_token **tokens)
{
	t_execcmd	cmd;
	t_token		*tok;

	tok = *tokens;
	cmd = (t_execcmd){0};
	while (tok && tok->type == TOKEN_WORD && cmd.argc < MAX_ARGS - 1)
	{
		cmd.argv[cmd.argc] = ft_strdup(tok->value);
		if (!cmd.argv[cmd.argc])
		{
			free_exec_argv(&cmd);
			return (print_error_null("Memory allocation error"));
		}
		cmd.argc++;
		tok = tok->next;
	}
	cmd.argv[cmd.argc] = NULL;
	*tokens = tok;
	return (set_exec_node(&cmd));
}
