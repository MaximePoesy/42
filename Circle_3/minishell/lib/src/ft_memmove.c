/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:14:06 by staverni          #+#    #+#             */
/*   Updated: 2024/08/20 18:28:00 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*p1;
	unsigned char		*p2;

	p1 = (const unsigned char *)src;
	p2 = (unsigned char *)dst;
	if (p1 == p2 || len == 0)
		return (dst);
	if (p2 < p1)
	{
		while (len--)
			*p2++ = *p1++;
	}
	else
	{
		p2 += len;
		p1 += len;
		while (len--)
			*(--p2) = *(--p1);
	}
	return (dst);
}
