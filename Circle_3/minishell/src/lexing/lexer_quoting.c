/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quoting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:00:00 by staverni          #+#    #+#             */
/*   Updated: 2025/04/29 19:35:39 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the closing single quote for a string segment.
 * Does NOT handle escapes, as '\' is literal within single quotes.
 * @param p_after Pointer to the character *after* the opening quote.
 * @param quote The quote character to find (should be '\'').
 * @return Pointer to the closing quote character,
 *         or NULL if not found before NUL.
 */
char	*find_closing_single_quote(char *p_after)
{
	char	*p;

	p = p_after;
	if (!p)
		return (NULL);
	while (*p != '\0')
	{
		if (*p == '\'')
			return (p);
		p++;
	}
	return (NULL);
}

/**
 * @brief Finds the closing double quote for a string segment,
 * skipping escaped quotes.
 *
 * Iterates through the string starting *after* the opening double quote.
 * Returns a pointer to the first unescaped double quote ('"') found.
 * Handles backslash escapes (e.g., '\"' is skipped because the '\' causes
 * the loop to advance by 2, but a quote after '\\' would be found).
 *
 * @param p_after Pointer to the character immediately *after*
 * the opening double quote.
 * @return char* Pointer to the closing double quote character,
 * or NULL if not found
 * before the end of the string (NUL character).
 */
char	*find_closing_double_quote(char *p_after)
{
	char	*p;

	p = p_after;
	if (!p)
		return (NULL);
	while (*p != '\0')
	{
		if (*p == '\\')
		{
			if (*(p + 1) != '\0')
				p += 2;
			else
				p++;
		}
		else if (*p == '\"')
			return (p);
		else
			p++;
	}
	return (NULL);
}

/**
 * @brief Finds the corresponding closing quote (' or "),
 * handling escapes appropriately.
 *
 * This function acts as a dispatcher, calling the correct finder function
 * based on the 'quote_char'. If the specific finder function returns NULL
 * (indicating an unclosed quote), this function writes a standard syntax error
 * message to stderr (file descriptor 2) and returns NULL.
 *
 * @param p_after Pointer to the character immediately *after*
 * the opening quote character.
 * @param quote_char            The quote character to search for (' or ").
 * @return char* Pointer to the closing quote character if found,
 * otherwise NULL (after printing an error for unclosed quotes).
 */
char	*find_closing_quote(char *p_after, char quote_char)
{
	char	*closing_quote_ptr;

	if (!p_after || *p_after == '\0')
		return (NULL);
	closing_quote_ptr = NULL;
	if (quote_char == '\'')
	{
		closing_quote_ptr = find_closing_single_quote(p_after);
		if (!closing_quote_ptr)
			write(2, "Syntax error: unclosed single quote\n", 36);
	}
	else if (quote_char == '\"')
	{
		closing_quote_ptr = find_closing_double_quote(p_after);
		if (!closing_quote_ptr)
			write(2, "Syntax error: unclosed double quote\n", 36);
	}
	else
		return (NULL);
	return (closing_quote_ptr);
}
