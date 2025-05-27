/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binop_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:11:01 by staverni          #+#    #+#             */
/*   Updated: 2025/04/25 14:59:45 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd *parse_binop(t_token **tokens)
// {
// 	t_cmd *left = parse_pipe(tokens);

// 	while (*tokens)
// 	{
// 		t_toktype t = (*tokens)->type;
// 		if (t != TOKEN_AND && t != TOKEN_OR)
// 			break;
// 		t_cmd *cmd = malloc(sizeof(t_cmd));
// 		cmd->type = (t == TOKEN_AND) ? AND : OR;
// 		*tokens = (*tokens)->next;
// 		cmd->u.pipe.left = left;
// 		cmd->u.pipe.right = parse_pipe(tokens);
// 		left = cmd;
// 	}
// 	return (left);
// }
