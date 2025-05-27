/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:36:50 by staverni          #+#    #+#             */
/*   Updated: 2025/05/17 15:09:45 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character is valid for an environment variable name.
 *
 * This function checks if the given character is alphanumeric or an underscore.
 * It is used to validate the characters in an environment variable name.
 *
 * @param c The character to check.
 * @return 1 if the character is valid, 0 otherwise.
 *         Valid characters are alphanumeric characters (a-z, A-Z, 0-9)
 *         and the underscore character ('_').
 */
int	is_valid_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

/**
 * @brief Compares a name against the name part of a "name=value" string.
 *
 * When searching a list where each node's content points to a string in the
 * format "name=value". It compares the 'name_ref' string (e.g., "USER") with
 * the part of the 'content' string before the first '=' (e.g., "USER" in
 * "USER=guest").
 *
 * @param content A void pointer expected to point to the "name=value" string
 * from a list node.
 * @param name_ref A void pointer expected to point to the name string being
 * searched for (without the '=' or value).
 * @return int 0 if the names match exactly (same length and content).
 * Returns a non-zero value otherwise.
 * Returns non-zero if inputs are NULL or if 'content' is malformed
 * (doesn't contain '=').
 */
int	compare_env_name(const void *content, const void *name_ref)
{
	const char	*env_string;
	const char	*name_to_find;
	const char	*equals_ptr;
	size_t		name_len_in_env;
	size_t		name_to_find_len;

	env_string = (const char *)content;
	name_to_find = (const char *)name_ref;
	if (!env_string || !name_to_find)
		return (1);
	equals_ptr = ft_strchr(env_string, '=');
	if (!equals_ptr)
		return (1);
	name_len_in_env = equals_ptr - env_string;
	name_to_find_len = ft_strlen(name_to_find);
	if (name_len_in_env != name_to_find_len)
		return (1);
	return (ft_strncmp(env_string, name_to_find, name_len_in_env));
}

/**
 * @brief Builds a string in the format "name=value" from the given name and
 * value.
 *
 * This function takes a name and a value, and constructs a dynamically
 * allocated string in the format "name=value". The caller is responsible for
 * freeing the returned string.
 *
 * @param name The name part of the environment variable.
 * @param value The value part of the environment variable.
 * @return A dynamically allocated string in the format "name=value", or NULL
 *         if memory allocation fails or if either name or value is NULL.
 */
char	*build_env_string(const char *name, const char *value)
{
	char	*env_string;
	size_t	name_len;
	size_t	value_len;

	if (!name || !value)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env_string = malloc(name_len + value_len + 2);
	if (!env_string)
		return (NULL);
	ft_strlcpy(env_string, name, name_len + 1);
	env_string[name_len] = '=';
	ft_strlcpy(env_string + name_len + 1, value, value_len + 1);
	return (env_string);
}

char	**list_to_envp(t_list *env)
{
	size_t	i;
	size_t	len;
	char	**envp;

	len = ft_lstsize(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (print_error_null("malloc"));
	i = 0;
	while (env)
	{
		envp[i++] = env->content;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
