/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:46:18 by staverni          #+#    #+#             */
/*   Updated: 2025/05/01 16:38:54 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the length of the unquoted segment starting at str.
 *
 * Scans the string to find the first unescaped quote (' or ") or the
 * null terminator. Takes backslash escaping into account.
 *
 * @param str The string to scan.
 * @return size_t The length of the unquoted segment.
 */
static size_t	get_unquoted_segment_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\\' && str[len + 1])
			len += 2;
		else if (str[len] == '\'' || str[len] == '\"')
			break ;
		else
			len++;
	}
	return (len);
}

/**
 * @brief Appends the expanded content of an unquoted string to the buffer.
 *
 * This function takes a buffer and a pointer to a string. It expands the
 * unquoted string and appends the result to the buffer.
 *
 * @param buff The buffer to append the expanded content to.
 * @param p Pointer to the caller's char pointer (pointing after opening quote).
 * This pointer will be advanced past the closing quote on success.
 * @return int 0 on success, 1 on failure (e.g., buffer append error).
 */
static int	append_unquoted_move(t_buffer *buff, char **p, t_list *env)
{
	char	*appendix;

	if (!buff || !p || !*p)
		return (1);
	appendix = expand_unquoted(*p, env);
	if (!appendix)
		return (1);
	if (!buffer_append(buff, appendix, ft_strlen(appendix)))
	{
		free(appendix);
		return (1);
	}
	free(appendix);
	*p += get_unquoted_segment_len(*p);
	return (0);
}

/**
 * @brief Appends the expanded content of a quoted string to the buffer.
 *
 * This function takes a buffer, a pointer to a string, and a quote character.
 * It expands the quoted string (either single or double quotes) and appends
 * the result to the buffer. The pointer is updated to point after the closing
 * quote.
 *
 * @param buff The buffer to append the expanded content to.
 * @param p Pointer to the caller's char pointer (pointing after opening quote).
 * This pointer will be advanced past the closing quote on success.
 * @param quote The quote character (' or ") used for expansion.
 * @return int 0 on success, 1 on failure (e.g., buffer append error).
 */
static int	append_quote_move(t_buffer *buff, char **p, char quote, t_list *env)
{
	char	*appendix;

	if (!buff || !p || !*p)
		return (1);
	if (quote == '\"')
		appendix = expand_double_quote(*p, env);
	else if (quote == '\'')
		appendix = expand_single_quote(*p);
	else
		return (1);
	if (!appendix)
		return (1);
	if (!buffer_append(buff, appendix, ft_strlen(appendix)))
	{
		free(appendix);
		return (1);
	}
	free(appendix);
	*p = find_closing_quote(*p + 1, quote) + 1;
	return (0);
}

/**
 * @brief Expands a word token by processing double quotes, single quotes,
 * and unquoted segments.
 *
 * This function iterates through the token string, expanding each segment
 * based on its type (double-quoted, single-quoted, or unquoted). It appends
 * the expanded content to the provided buffer.
 *
 * @param buf The buffer to append the expanded content to.
 * @param p_ptr Pointer to the caller's char pointer (after opening quote).
 * This pointer will be advanced past the closing quote on success.
 * @return int 0 on success, 1 on failure (e.g., buffer append error).
 */
static int	expand_word_loop(t_buffer *buf, char *p, t_list *env)
{
	if (!buf || !p || !*p)
		return (1);
	while (*p)
	{
		if (*p == '\"')
		{
			if (append_quote_move(buf, &p, '\"', env))
				return (1);
		}
		else if (*p == '\'')
		{
			if (append_quote_move(buf, &p, '\'', env))
				return (1);
		}
		else
		{
			if (append_unquoted_move(buf, &p, env))
				return (1);
		}
	}
	return (0);
}

/**
 * @brief Expands a word token.
 *
 * This function takes a token string and expands it by processing
 * double quotes, single quotes, and unquoted segments. It appends
 * the expanded content to a buffer and returns the final expanded string.
 *
 * @param token The token string to be expanded.
 * @return char* A newly allocated string containing the expanded content.
 *               NULL if expansion fails or if the input is NULL.
 */
char	*expand_word(char *token, t_list *env)
{
	char		*p;
	char		*append;
	int			loop_status;
	t_buffer	buf;

	if (!token)
		return (print_error_null("Error: expansion failed"));
	if (!buffer_init(&buf, 128))
		return (print_error_null("Error: buffer initialization failed"));
	p = token;
	loop_status = expand_word_loop(&buf, p, env);
	if (loop_status == 1)
	{
		buffer_free_data(&buf);
		return (print_error_null("Error: expansion failed 2"));
	}
	if (assign_buffer(&buf, &append))
		return (print_error_null("Error: buffer assignment failed"));
	return (append);
}
