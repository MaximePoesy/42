/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:46 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/04 16:12:59 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_x(unsigned int nbr)
{
	char			buffer[8];
	int				index;
	unsigned int	digit;

	index = 0;
	if (nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (nbr > 0)
	{
		digit = nbr % 16;
		if (digit < 10)
			buffer[index++] = digit + '0';
		else
			buffer[index++] = (digit - 10) + 'a';
		nbr /= 16;
	}
	while (index > 0)
		write(1, &buffer[--index], 1);
	return (index);
}
