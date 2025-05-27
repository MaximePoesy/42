/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:06:54 by staverni          #+#    #+#             */
/*   Updated: 2025/05/17 15:04:15 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks the length of a variable name starting with '$'.
 *
 * This function checks if the token starts with '$' and determines the length
 * of the variable name that follows. It handles special cases like '$?' for
 * the last exit status and checks for valid characters in the variable name.
 *
 * @param token_start The start of the token string.
 * @return The length of the variable name, including the '$' character.
 *         Returns 0 if the token does not start with '$' or if the variable
 *         name is invalid.
 *         Returns 1 if the token is just '$'.
 *         Returns 2 if the token is '$?'.
 */
size_t	get_dollar_len(const char *token_start)
{
	size_t	name_len;

	if (!token_start || *token_start != '$')
		return (0);
	if (*(token_start + 1) == '?')
		return (2);
	name_len = 0;
	while (*(token_start + 1 + name_len)
		&& is_valid_char(*(token_start + 1 + name_len)))
		name_len++;
	if (name_len > 0)
		return (1 + name_len);
	return (1);
}

/**
 * @brief Expands an environment variable or gets the last exit status.
 *
 * This function takes a token string that starts with '$' and checks if it
 * corresponds to an environment variable. If it does, it retrieves the value
 * of that variable. If the token is '$?', it returns the last exit status.
 *
 * @param buf The buffer to store the expanded value.
 * @param token The token string to be expanded.
 * @return The expanded value of the environment variable or NULL if not found.
 *         The caller is responsible for freeing the returned string.
 */
char	*dollar_expansion(char *token, t_list *env)
{
	if (!token || *token != '$')
		return (NULL);
	if (*(token + 1) == '?')
		return (ft_itoa(g_exit_status));
	else if (*(token + 1) == '\0' || *(token + 1) == '$')
		return (ft_strdup("$"));
	return (get_env_var(token + 1, env));
}

/**
 * @brief Handles dollar expansion in a token.
 *
 * This function takes a token string that starts with '$' and expands it
 * by retrieving the value of the corresponding environment variable or
 * the last exit status. It appends the expanded value to the provided buffer.
 *
 * @param buf The buffer to append the expanded value to.
 * @param token The token string to be expanded.
 * @return The length of the variable name, including the '$' character.
 *         Returns -1 on failure (e.g., buffer append error).
 */
size_t	apply_dollar_expansion(t_buffer *buf, char *token, t_list *env)
{
	char	*expanded_value;

	expanded_value = dollar_expansion(token, env);
	if (expanded_value)
	{
		if (!buffer_append(buf, expanded_value, ft_strlen(expanded_value)))
		{
			free(expanded_value);
			return (-1);
		}
	}
	free(expanded_value);
	return (get_dollar_len(token));
}

/**
 * @brief Handles backslash expansion in quotes.
 *
 * This function handles backslash expansion for characters that are escaped
 * within quotes. It returns a dynamically allocated string containing the
 * expanded value.
 *
 * @param p The token string to be expanded.
 * @param in_quotes Indicates if the token is within quotes.
 * @return A dynamically allocated string containing the expanded value.
 *         The caller is responsible for freeing the returned string.
 */
char	*backslash_expansion(char *p, int in_quotes)
{
	if (in_quotes)
	{
		if (p[1] == '$' || p[1] == '\"' || p[1] == '\\' || p[1] == '\'')
			return (ft_strndup(p + 1, 1));
		else
			return (ft_strndup(p, 2));
	}
	else
		return (ft_strndup(p + 1, 1));
}

/**
 * @brief Handles backslash expansion in a token.
 *
 * This function takes a token string that starts with a backslash and expands
 * it by retrieving the corresponding character. It appends the expanded value
 * to the provided buffer.
 *
 * @param buf The buffer to append the expanded value to.
 * @param token The token string to be expanded.
 * @param in_quotes Indicates if the token is within quotes.
 * @return The length of the variable name, including the '$' character.
 *         Returns -1 on failure (e.g., buffer append error).
 */
size_t	apply_backslash_expansion(t_buffer *buf, char *token, int in_quotes)
{
	char	*expanded_value;

	expanded_value = backslash_expansion(token, in_quotes);
	if (expanded_value)
	{
		if (!buffer_append(buf, expanded_value, ft_strlen(expanded_value)))
		{
			free(expanded_value);
			return (-1);
		}
		free(expanded_value);
	}
	else
		return (-1);
	return (2);
}
