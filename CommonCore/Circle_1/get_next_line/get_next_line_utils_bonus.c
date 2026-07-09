/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:58:22 by gemartin          #+#    #+#             */
/*   Updated: 2024/12/12 11:12:40 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = malloc(len1 + len2 + 1);
	if (!joined_str)
		return (free_and_nullify(&s1));
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			joined_str[i] = s1[i];
		else
			joined_str[i] = s2[i - len1];
		i++;
	}
	joined_str[i] = '\0';
	free(s1);
	return (joined_str);
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str != NULL && str[length] != '\0')
		length++;
	return (length);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (str == NULL || start >= ft_strlen(str))
	{
		substring = malloc(1);
		if (substring != NULL)
			substring[0] = '\0';
		return (substring);
	}
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	substring = malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < len && str[start + i] != '\0')
	{
		substring[i] = str[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
