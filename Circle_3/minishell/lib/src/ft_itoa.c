/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:45:28 by staverni          #+#    #+#             */
/*   Updated: 2024/08/25 18:00:54 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	nb_len;

	if (n == 0)
		return (1);
	nb_len = 0;
	if (n < 0)
		nb_len += 1;
	while (n != 0)
	{
		n /= 10;
		nb_len++;
	}
	return (nb_len);
}

char	*ft_itoa(int n)
{
	int				nb_len;
	int				offset;
	unsigned int	un;
	char			*dest;

	nb_len = intlen(n);
	dest = (char *)malloc(sizeof(char) * (nb_len + 1));
	if (!dest)
		return (NULL);
	dest[nb_len] = '\0';
	offset = 0;
	if (n < 0)
	{
		dest[0] = '-';
		un = -n;
		offset++;
	}
	else
		un = n;
	while (nb_len-- - offset > 0)
	{
		dest[nb_len] = un % 10 + '0';
		un /= 10;
	}
	return (dest);
}
