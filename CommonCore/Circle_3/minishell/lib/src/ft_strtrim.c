/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:50:25 by staverni          #+#    #+#             */
/*   Updated: 2024/10/25 13:49:54 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && is_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && is_set(s1[len - 1], set))
		len--;
	dest = (char *)malloc((sizeof(char) * len) + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
