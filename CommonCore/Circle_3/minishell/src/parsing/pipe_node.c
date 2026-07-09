/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:05 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 22:15:22 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pipe_node(t_cmd **pipe_node, t_cmd *left, t_cmd *right)
{
	*pipe_node = malloc(sizeof(t_cmd));
	if (!*pipe_node)
	{
		print_error_null("malloc");
		free_cmd_tree(left);
		free_cmd_tree(right);
		return (1);
	}
	(*pipe_node)->type = PIPE;
	(*pipe_node)->u.pipe.left = left;
	(*pipe_node)->u.pipe.right = right;
	return (0);
}

t_cmd	*parse_pipe(t_token **tokens)
{
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*pipe_node;

	left = parse_redirect(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_redirect(tokens);
		if (!right)
		{
			free_cmd_tree(left);
			return (NULL);
		}
		if (set_pipe_node(&pipe_node, left, right))
			return (NULL);
		left = pipe_node;
	}
	return (left);
}
