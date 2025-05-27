/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:40:36 by staverni          #+#    #+#             */
/*   Updated: 2025/05/03 17:06:43 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_token_end(char *input)
{
	char	*p;
	char	*closing_quote_ptr;

	p = input;
	while (*p && !ft_strchr(WHITESPACES METACHARS, *p))
	{
		if (*p == '\"' || *p == '\'')
		{
			closing_quote_ptr = find_closing_quote(p + 1, *p);
			if (!closing_quote_ptr)
				return (NULL);
			p = closing_quote_ptr + 1;
		}
		else if (*p == '\\' && (*(p + 1) != '\0'))
			p += 2;
		else
			++p;
	}
	return (p);
}

t_token	*extract_quote(char **input, char *end)
{
	t_token	*token;

	token = create_token(token_type(end), *input, end - *input + 1);
	*input = end + 1;
	return (token);
}

t_token	*extract_metachar(char **input)
{
	t_token	*token;
	int		max_len;
	char	c[3];
	int		offset;

	offset = 1;
	ft_bzero(c, sizeof(c));
	c[0] = (*input)[0];
	c[1] = (*input)[1];
	max_len = max_metachar_len(c[0]);
	if (c[0] == c[1] && max_len == 2)
		offset = 2;
	if (!is_supported_metachar(c))
		return (token_syntax_error(c, offset));
	token = create_token(token_type(c), c, offset);
	*input += offset;
	return (token);
}

t_token	*get_next_token(char **input)
{
	char	*start;
	char	*end;

	(*input) += ft_strspn(*input, WHITESPACES);
	start = *input;
	if (**input == '\0')
		return (NULL);
	else if (ft_strchr(METACHARS, **input))
		return (extract_metachar(input));
	else if (**input == '\"' || **input == '\'')
	{
		end = find_closing_quote(*input + 1, **input);
		if (!end)
			return (NULL);
		if (ft_strchr(WHITESPACES METACHARS, *(end + 1)))
			return (extract_quote(input, end));
	}
	end = find_token_end(*input);
	if (!end)
		return (NULL);
	*input = end;
	return (create_token(TOKEN_WORD, start, end - start));
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	if (!input)
		return (NULL);
	head = NULL;
	tail = NULL;
	token = get_next_token(&input);
	while (token)
	{
		if (!head)
			head = token;
		else
			tail->next = token;
		tail = token;
		token = get_next_token(&input);
	}
	if (*input)
	{
		ft_token_iter(head, free_token);
		return (NULL);
	}
	return (head);
}
