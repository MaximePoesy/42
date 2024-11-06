/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:06:41 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/04 16:16:40 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	put_nbr_unsigned(int nbr, int num)
{
	unsigned int	number;
	char			digit;

	number = 0;
	if (nbr > 9)
	{
		num = put_nbr_unsigned(nbr / 10, num + 1);
	}
	digit = (nbr % 10) + '0';
	write(1, &digit, 1);
	return (num);
}

int	print_u(unsigned int nbr)
{
	int	num;

	num = put_nbr_unsigned(nbr, 0);
	return (num + 1);
}
