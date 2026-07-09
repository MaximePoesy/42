/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:28:46 by staverni          #+#    #+#             */
/*   Updated: 2025/03/17 17:00:38 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	char	*p;
	char	*a;
	size_t	count;

	count = 0;
	p = (char *)s;
	while (*p)
	{
		a = (char *)accept;
		while (*a)
		{
			if (*p == *a)
			{
				count++;
				break ;
			}
			a++;
		}
		if (!*a)
			break ;
		p++;
	}
	return (count);
}
