/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:33:43 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 17:25:49 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_metachar_repetition(t_token *tokens)
{
	t_token		*current;
	t_toktype	prev_type;
	t_toktype	current_type;

	current = tokens;
	prev_type = TOKEN_UNKNOWN;
	while (current)
	{
		current_type = current->type;
		if (current_type == prev_type && current_type != TOKEN_WORD)
		{
			token_syntax_error(current->value, ft_strlen(current->value));
			return (0);
		}
		prev_type = current_type;
		current = current->next;
	}
	return (1);
}

static int	check_redirection_file(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (token_is_redir(current->type))
		{
			if (!current->next)
			{
				token_syntax_error("newline", 7);
				return (0);
			}
			if (current->next->type != TOKEN_WORD)
			{
				token_syntax_error(current->value, ft_strlen(current->value));
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

static int	check_word_around_pipe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == TOKEN_PIPE)
	{
		token_syntax_error(current->value, ft_strlen(current->value));
		return (0);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				token_syntax_error(current->value, ft_strlen(current->value));
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	pre_validate(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!check_metachar_repetition(tokens))
		return (0);
	else if (!check_word_around_pipe(tokens))
		return (0);
	else if (!check_redirection_file(tokens))
		return (0);
	return (1);
}
