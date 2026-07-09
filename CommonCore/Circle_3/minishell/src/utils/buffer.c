/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:23:44 by staverni          #+#    #+#             */
/*   Updated: 2025/05/17 14:52:13 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes a buffer with a specified initial capacity.
 *
 * This function allocates memory for the buffer's data and sets its initial
 * length and capacity. If the initial capacity is 0, it defaults to 1.
 * The buffer is null-terminated.
 *
 * @param buf A pointer to the buffer to initialize.
 * @param initial_capacity The initial capacity of the buffer.
 * @return 1 if the buffer is successfully initialized, 0 otherwise.
 *         The buffer's data is allocated with malloc, and the caller is
 *         responsible for freeing it later.
 *         The buffer's length is set to 0, and the data is null-terminated.
 *         If the allocation fails, the buffer's data is set to NULL, and
 *         the length and capacity are set to 0.
 *         If the initial capacity is 0, it defaults to 1.
 *         If the buffer is NULL, the function does nothing and returns 0.
 */
int	buffer_init(t_buffer *buf, size_t initial_capacity)
{
	if (initial_capacity == 0)
		initial_capacity = 1;
	buf->data = malloc(initial_capacity);
	if (!buf->data)
		return (0);
	buf->data[0] = '\0';
	buf->len = 0;
	buf->capacity = initial_capacity;
	return (1);
}

/**
 * @brief Appends a string to the buffer.
 *
 * This function appends a specified number of characters from the given
 * string to the buffer. If the buffer does not have enough capacity,
 * it reallocates memory for the buffer's data.
 *
 * @param buf A pointer to the buffer to append to.
 * @param str The string to append.
 * @param len_to_append The number of characters to append from the string.
 * @return 1 if the string is successfully appended, 0 otherwise.
 *         The buffer's data is null-terminated after appending.
 *         If the buffer is NULL or the string is NULL, or if
 *         len_to_append is 0, the function does nothing and returns 0.
 */
int	buffer_append(t_buffer *buf, const char *str, size_t len_to_append)
{
	size_t	required;
	size_t	new_capacity;
	char	*new_data;

	if (!buf || !str || len_to_append == 0)
		return (1);
	required = buf->len + len_to_append + 1;
	if (required > buf->capacity)
	{
		new_capacity = buf->capacity * 2;
		if (new_capacity < required)
			new_capacity = required;
		new_data = ft_realloc(buf->data, buf->capacity, new_capacity);
		if (!new_data)
			return (0);
		buf->data = new_data;
		buf->capacity = new_capacity;
	}
	ft_memcpy(buf->data + buf->len, str, len_to_append);
	buf->len += len_to_append;
	buf->data[buf->len] = '\0';
	return (1);
}

/**
 * @brief Finalizes the buffer by reallocating its data to fit its length.
 *
 * This function reallocates the buffer's data to fit its current length
 * and null-terminates the string. It returns a pointer to the final string.
 *
 * @param buf A pointer to the buffer to finalize.
 * @return A pointer to the final string if successful, NULL otherwise.
 *         The buffer's data is reallocated with realloc, and the caller
 *         is responsible for freeing it later.
 *         If the buffer is NULL or its data is NULL, the function returns NULL.
 */
char	*buffer_finalize(t_buffer *buf)
{
	char	*final_str;

	if (!buf || !buf->data)
		return (NULL);
	final_str = ft_realloc(buf->data, buf->capacity, buf->len + 1);
	if (!final_str)
		return (NULL);
	buf->data = final_str;
	buf->capacity = buf->len + 1;
	return (final_str);
}

/**
 * @brief Frees the data of the buffer and resets its length and capacity.
 *
 * This function frees the memory allocated for the buffer's data and
 * resets its length and capacity to 0. The buffer itself is not freed.
 *
 * @param buf A pointer to the buffer to free data from.
 *            If the buffer is NULL, the function does nothing.
 */
void	buffer_free_data(t_buffer *buf)
{
	if (buf)
	{
		if (buf->data)
			free(buf->data);
		buf->data = NULL;
		buf->len = 0;
		buf->capacity = 0;
	}
}

/**
 * @brief Assigns the buffer's data to a string and frees the buffer.
 *
 * This function finalizes the buffer, duplicates its data into a new string,
 * and frees the buffer's data. The caller is responsible for freeing the
 * returned string.
 *
 * @param buf A pointer to the buffer to assign.
 * @param str A pointer to a string pointer where the final string will be
 *            assigned. The caller is responsible for freeing this string.
 * @return 0 if successful, 1 if an error occurs.
 */
int	assign_buffer(t_buffer *buf, char **str)
{
	char	*final_str;

	if (!buf)
		return (1);
	if (!buffer_finalize(buf))
	{
		buffer_free_data(buf);
		return (1);
	}
	final_str = ft_strdup(buf->data);
	if (!final_str)
	{
		buffer_free_data(buf);
		return (1);
	}
	buffer_free_data(buf);
	*str = final_str;
	return (0);
}
