/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:46:32 by staverni          #+#    #+#             */
/*   Updated: 2025/04/29 19:37:28 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes the content within single quotes literally.
 *
 * Iterates from the character after the opening quote (*p_ptr) until
 * the closing quote or end of string. Appends the literal content
 * to the buffer. Updates *p_ptr to point after the closing quote
 * on success.
 *
 * @param buf The buffer to append the literal content to.
 * @param p_ptr Pointer to the caller's char pointer (after opening quote).
 * This pointer will be advanced past the closing quote on success.
 * @return int 0 on success, 1 on failure (buffer error or unterminated quote).
 */
int	expand_single_quote_loop(t_buffer *buf, char *p)
{
	char	*closing_quote;

	if (!buf || !p)
		return (1);
	closing_quote = find_closing_single_quote(p);
	if (!closing_quote)
		return (1);
	while (p != closing_quote)
	{
		if (!buffer_append(buf, p, 1))
			return (1);
		++p;
	}
	return (0);
}

/**
 * @brief Expands a single-quoted token.
 *
 * Creates a new string containing the literal content within the single quotes.
 * Handles initialization, cleanup, and errors.
 *
 * @param token The token string, expected to start with '.
 * @return char* A newly allocated string with the literal content,
 * or NULL if input is NULL, memory allocation fails,
 * or the quote is unterminated.
 */
char	*expand_single_quote(char *token)
{
	char		*p;
	char		*append;
	t_buffer	buf;
	int			loop_status;

	if (!token)
		return (print_error_null("Error: expansion failed"));
	if (!buffer_init(&buf, 64))
		return (print_error_null("Error: buffer initialization failed"));
	p = token;
	if (*p == '\'')
		++p;
	loop_status = expand_single_quote_loop(&buf, p);
	if (loop_status == 1)
	{
		buffer_free_data(&buf);
		return (print_error_null("Error: expansion loop failed"));
	}
	if (assign_buffer(&buf, &append))
		return (print_error_null("Error: buffer assignment failed"));
	return (append);
}
