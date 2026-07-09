/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:10:42 by staverni          #+#    #+#             */
/*   Updated: 2025/04/29 19:36:02 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_value(t_toktype type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_AND)
		return ("&&");
	if (type == TOKEN_OR)
		return ("||");
	if (type == TOKEN_REDIRECT_IN)
		return ("<");
	if (type == TOKEN_REDIRECT_OUT)
		return (">");
	if (type == TOKEN_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	if (type == TOKEN_SINGLE_QUOTE)
		return ("'");
	if (type == TOKEN_DOUBLE_QUOTE)
		return ("\"");
	return (NULL);
}

t_toktype	token_type(char *value)
{
	if (!ft_strncmp(value, "||", 2))
		return (TOKEN_OR);
	if (!ft_strncmp(value, "|", 1))
		return (TOKEN_PIPE);
	if (!ft_strncmp(value, "&&", 2))
		return (TOKEN_AND);
	if (!ft_strncmp(value, ">>", 2))
		return (TOKEN_APPEND);
	if (!ft_strncmp(value, ">", 1))
		return (TOKEN_REDIRECT_OUT);
	if (!ft_strncmp(value, "<<", 2))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(value, "<", 1))
		return (TOKEN_REDIRECT_IN);
	if (!ft_strncmp(value, "'", 1))
		return (TOKEN_SINGLE_QUOTE);
	if (!ft_strncmp(value, "\"", 1))
		return (TOKEN_DOUBLE_QUOTE);
	return (TOKEN_WORD);
}

t_token	*create_token(t_toktype type, char *value, size_t len)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strndup(value, len);
	token->next = NULL;
	return (token);
}

void	replace_token(t_token *token, char *new_value)
{
	if (!token || !new_value)
		return ;
	free(token->value);
	token->value = new_value;
}

void	free_token(t_token *head)
{
	free(head->value);
	free(head);
}
