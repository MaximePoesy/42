/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:01:12 by staverni          #+#    #+#             */
/*   Updated: 2025/04/21 15:22:19 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token *token, t_list *env)
{
	char	*expanded_value;

	if (!token)
		return ;
	expanded_value = NULL;
	if (token->type == TOKEN_DOUBLE_QUOTE)
		expanded_value = expand_double_quote(token->value, env);
	else if (token->type == TOKEN_SINGLE_QUOTE)
		expanded_value = expand_single_quote(token->value);
	else if (token->type == TOKEN_WORD)
		expanded_value = expand_word(token->value, env);
	if (expanded_value)
	{
		replace_token(token, expanded_value);
		token->type = TOKEN_WORD;
	}
}

void	expand(t_token *tokens, t_list *env)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		expander(current, env);
		current = current->next;
	}
}
