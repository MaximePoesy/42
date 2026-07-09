/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:09:32 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 23:13:23 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redir_node_type(t_cmd *node, t_toktype type)
{
	if (type == TOKEN_REDIRECT_IN)
		node->type = REDIR_IN;
	else if (type == TOKEN_REDIRECT_OUT)
		node->type = REDIR_OUT;
	else if (type == TOKEN_APPEND)
		node->type = REDIR_APPEND;
	else if (type == TOKEN_HEREDOC)
		node->type = REDIR_HEREDOC;
	return (0);
}

static t_cmd	*init_redir_node(t_cmd *cmd, t_token **tokens)
{
	t_cmd	*redir_node;

	redir_node = malloc(sizeof(t_cmd));
	if (!redir_node)
	{
		free_cmd_tree(cmd);
		return (NULL);
	}
	ft_bzero(redir_node, sizeof(t_cmd));
	set_redir_node_type(redir_node, (*tokens)->type);
	redir_node->u.redir.cmd = cmd;
	redir_node->u.redir.file = NULL;
	(*tokens) = (*tokens)->next;
	redir_node->u.redir.file = ft_strdup((*tokens)->value);
	if (!redir_node->u.redir.file)
	{
		free(redir_node);
		free_cmd_tree(cmd);
		return (NULL);
	}
	(*tokens) = (*tokens)->next;
	return (redir_node);
}

static t_cmd	*get_innermost_cmd(t_cmd *cmd)
{
	while (cmd && cmd->type != CMD)
		cmd = cmd->u.redir.cmd;
	return (cmd);
}

static void	additional_args(t_cmd *cmd, t_token **tokens)
{
	t_token		*tok;
	t_execcmd	*exec;

	if (!cmd || cmd->type != CMD || !(*tokens))
		return ;
	tok = *tokens;
	exec = &cmd->u.exec;
	while (tok && tok->type == TOKEN_WORD && exec->argc < MAX_ARGS - 1)
	{
		exec->argv[exec->argc] = ft_strdup(tok->value);
		if (!exec->argv[exec->argc])
		{
			free_cmd_tree(cmd);
			return ;
		}
		exec->argc++;
		tok = tok->next;
	}
	exec->argv[exec->argc] = NULL;
	*tokens = tok;
}

t_cmd	*parse_redirect(t_token **tokens)
{
	t_cmd	*cmd;
	t_cmd	*redir_node;
	t_cmd	*exec_cmd;

	cmd = parse_exec(tokens);
	if (!cmd)
		if ((*tokens) && !token_is_redir((*tokens)->type))
			return (NULL);
	while (*tokens && token_is_redir((*tokens)->type))
	{
		redir_node = init_redir_node(cmd, tokens);
		if (!redir_node)
			return (print_error_null("Memory allocation error"));
		exec_cmd = get_innermost_cmd(redir_node);
		if (exec_cmd)
			additional_args(exec_cmd, tokens);
		cmd = redir_node;
	}
	return (cmd);
}
