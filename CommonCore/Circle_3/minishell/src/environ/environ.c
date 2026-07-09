/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:46:05 by staverni          #+#    #+#             */
/*   Updated: 2025/05/01 16:38:09 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts the global `environ` variable to a linked list.
 *
 * This function iterates through the global `environ` variable, which is an
 * array of strings representing environment variables in the format
 * "name=value". It creates a linked list where each node contains one of these
 * strings. The function returns a pointer to the head of the linked list.
 *
 * @return A pointer to the head of the linked list containing environment
 *         variables. Returns NULL if memory allocation fails.
 */
t_list	*environ_to_list(void)
{
	t_list	*env_list;
	t_list	*new_node;
	size_t	i;

	env_list = NULL;
	i = 0;
	while (environ[i])
	{
		new_node = ft_lstnew(ft_strdup(environ[i]));
		if (!new_node)
		{
			if (env_list)
				ft_lstclear(&env_list, free);
			return (print_error_null("Memory allocation error"));
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

/**
 * @brief Retrieves the value of an environment variable.
 *
 * This function searches for the variable in a linked list of environment
 * variables. If the variable is found, its value is returned.
 * If the variable is not found, NULL is returned.
 *
 * @param var The name of the environment variable to retrieve.
 * @return A dynamically allocated string containing the value of the
 *         environment variable if it exists, or NULL if the variable
 *         does not exist. The caller is responsible for freeing the
 *         returned string.
 *         If the variable name is "?", the function returns the last
 *         exit status as a string.
 *         If the variable name is NULL or empty, the function returns NULL.
 */
char	*ft_getenv(char *var, t_list *env)
{
	char	*value_ptr;
	t_list	*found_node;

	if (!var || !*var)
		return (NULL);
	if (var[0] == '?')
		return (ft_itoa(g_exit_status));
	found_node = ft_lstfind(env, var, compare_env_name);
	if (!found_node || !found_node->content)
		return (NULL);
	value_ptr = env_value(found_node->content);
	return (value_ptr);
}

/**
 * @brief Retrieves the name part of an environment variable string.
 *
 * This function takes a string in the format "name=value" and returns a
 * dynamically allocated string containing only the name part (up to the
 * first '=' character). If the input string is NULL or does not contain an
 * '=', the function returns NULL.
 *
 * @param env_string The input string in the format "name=value".
 * @return A dynamically allocated string containing the name part, or NULL
 *         if the input string is NULL or malformed.
 */
char	*env_name(const char *env_string)
{
	const char	*equals_ptr;

	if (!env_string)
		return (NULL);
	equals_ptr = ft_strchr(env_string, '=');
	if (!equals_ptr)
		return (NULL);
	return (ft_strndup((char *)env_string, equals_ptr - env_string));
}

/**
 * @brief Retrieves the value part of an environment variable string.
 *
 * This function takes a string in the format "name=value" and returns a
 * dynamically allocated string containing only the value part (after the
 * first '=' character). If the input string is NULL or does not contain an
 * '=', the function returns NULL.
 *
 * @param env_string The input string in the format "name=value".
 * @return A dynamically allocated string containing the value part, or NULL
 *         if the input string is NULL or malformed.
 */
char	*env_value(const char *env_string)
{
	const char	*equals_ptr;

	if (!env_string)
		return (NULL);
	equals_ptr = ft_strchr(env_string, '=');
	if (!equals_ptr)
		return (NULL);
	return (ft_strdup(equals_ptr + 1));
}

/**
 * @brief Retrieves the value of an environment variable from its name.
 *
 * This function takes a pointer to the start of an environment variable name,
 * so without the '$' character. It checks if the variable name is valid,
 * and retrieves its value from the environment. If the variable
 * name is invalid or the variable does not exist, the function returns NULL.
 *
 * @param var_start Pointer to the start of the environment variable name.
 *                  The name must consist of valid characters as determined
 *                  by the `is_valid_char` function.
 *
 * @return A dynamically allocated string containing the value of the
 *         environment variable if it exists, or NULL if the variable
 *         name is invalid or the variable does not exist. The caller
 *         is responsible for freeing the returned string.
 */
char	*get_env_var(char *var_start, t_list *env)
{
	char	*env_var_name;
	char	*value;
	size_t	name_len;

	if (!var_start || !is_valid_char(*var_start))
		return (NULL);
	name_len = 0;
	while (var_start[name_len] && is_valid_char(var_start[name_len]))
		name_len++;
	env_var_name = ft_strndup(var_start, name_len);
	if (!env_var_name)
		return (NULL);
	value = ft_getenv(env_var_name, env);
	free(env_var_name);
	return (value);
}
