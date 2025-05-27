/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:46:01 by staverni          #+#    #+#             */
/*   Updated: 2025/04/20 11:52:47 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands a double-quoted string by replacing variables and escape
 * characters with their corresponding values.
 *
 * This function processes the input string character by character, handling
 * variable expansion and escape sequences. It uses a buffer to store the
 * expanded result. The function handles the following cases:
 * - Variables prefixed with '$' are expanded using the `apply_dollar_expansion`
 *   function.
 * - Escape sequences prefixed with '\' are expanded using the
 *   `apply_backslash_expansion` function.
 * - Any other characters are appended to the buffer as-is.
 *
 * The function continues until it encounters the closing double quote or the
 * end of the string. If the closing double quote is not found, the function
 * returns an error.
 *
 * @param buf A pointer to the buffer where the expanded result will be stored.
 * @param p A pointer to the current position in the input string.
 * @return 0 on success, or 1 if an error occurs during expansion.
 */
int	expand_double_quote_loop(t_buffer *buf, char *p, t_list *env)
{
	size_t	consumed_len;

	while (*p && *p != '\"')
	{
		consumed_len = 1;
		if (*p == '$')
			consumed_len = apply_dollar_expansion(buf, p, env);
		else if (*p == '\\' && p[1])
			consumed_len = apply_backslash_expansion(buf, p, 1);
		else
			if (!buffer_append(buf, p, 1))
				return (1);
		if (consumed_len < 0)
			return (1);
		p += consumed_len;
	}
	return (0);
}

/**
 * @brief Expands a double-quoted string by replacing variables and escape
 * characters with their corresponding values.
 *
 * This function initializes a buffer and calls the `expand_double_quote_loop`
 * function to perform the actual expansion. It handles the case where the
 * input string starts with a double quote.
 *
 * @param token The input string to be expanded.
 * @return A dynamically allocated string containing the expanded result, or NULL
 *         if an error occurs during expansion.
 */
char	*expand_double_quote(char *token, t_list *env)
{
	char		*p;
	char		*append;
	int			loop_status;
	t_buffer	buf;

	if (!token)
		return (print_error_null("Error: expansion failed"));
	if (!buffer_init(&buf, 64))
		return (print_error_null("Error: buffer initialization failed"));
	p = token;
	if (*p == '\"')
		++p;
	loop_status = expand_double_quote_loop(&buf, p, env);
	if (loop_status == 1)
	{
		buffer_free_data(&buf);
		return (print_error_null("Error: expansion failed"));
	}
	if (assign_buffer(&buf, &append))
		return (print_error_null("Error: buffer assignment failed"));
	return (append);
}
