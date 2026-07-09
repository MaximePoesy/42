/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:22:21 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 17:23:31 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the token type is a redirection type.
 * @param type The token type to check.
 * @return 1 if the type is a redirection type, 0 otherwise.
 */
int	token_is_redir(t_toktype type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

/**
 * Checks if the command type is a redirection type.
 * @param t The command type to check.
 * @return 1 if the type is a redirection type, 0 otherwise.
 */
int	node_is_redir(t_cmdtype t)
{
	return (t == REDIR_IN || t == REDIR_OUT || t == REDIR_APPEND
		|| t == REDIR_HEREDOC);
}
