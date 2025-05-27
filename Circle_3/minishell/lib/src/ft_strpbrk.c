/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:38:01 by staverni          #+#    #+#             */
/*   Updated: 2025/03/17 16:57:02 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	const char	*a;

	while (*s)
	{
		a = accept;
		while (*a)
			if (*a++ == *s)
				return ((char *)s);
		s++;
	}
	return (NULL);
}
