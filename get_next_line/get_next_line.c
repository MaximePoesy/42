/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:41:32 by gemartin          #+#    #+#             */
/*   Updated: 2024/12/12 10:17:24 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_nullify(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*newline_pos;
	size_t	offset;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos == NULL)
	{
		free_and_nullify(&buffer);
		return (NULL);
	}
	offset = 0;
	while (buffer + offset != newline_pos + 1)
		offset++;
	if (buffer[offset] == '\0')
	{
		free_and_nullify(&buffer);
		return (NULL);
	}
	new_buffer = ft_substr(buffer, offset, ft_strlen(buffer) - offset);
	free_and_nullify(&buffer);
	if (new_buffer == NULL)
		return (NULL);
	return (new_buffer);
}

char	*extract_line(char *buffer)
{
	char	*line;
	char	*newline_pos;
	size_t	length;

	newline_pos = ft_strchr(buffer, '\n');
	length = 0;
	while (buffer + length != newline_pos + 1 && buffer[length] != '\0')
		length++;
	line = ft_substr(buffer, 0, length);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*read_and_append(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (free_and_nullify(&buffer));
	temp_buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			temp_buffer[bytes_read] = '\0';
			buffer = ft_strjoin(buffer, temp_buffer);
			if (buffer == NULL)
				break ;
		}
	}
	free(temp_buffer);
	if (bytes_read == -1)
		return (free_and_nullify(&buffer));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL || ft_strchr(buffer, '\n') == NULL)
		buffer = read_and_append(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = extract_line(buffer);
	if (line == NULL)
	{
		free_and_nullify(&buffer);
		return (NULL);
	}
	buffer = update_buffer(buffer);
	return (line);
}
