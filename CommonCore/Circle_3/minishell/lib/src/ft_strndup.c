/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:20:34 by staverni          #+#    #+#             */
/*   Updated: 2025/04/20 12:16:46 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	char	*ptr;
	size_t	len;

	len = 0;
	while (src[len] && len < n)
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!(dest))
		return (NULL);
	ptr = dest;
	while (*src && len--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
