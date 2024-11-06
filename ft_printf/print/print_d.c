/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:53:37 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/04 15:30:15 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr(int nbr, int num)
{
	char	number;

	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (num);
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		num = ft_putnbr(nbr / 10, num + 1);
		number = (nbr % 10) + '0';
		write(1, &number, 1);
	}
	else
	{
		number = nbr + '0';
		write(1, &number, 1);
	}
	return (num);
}

int	print_d(int nbr)
{
	int	num;

	num = ft_putnbr(nbr, 0);
	return (num);
}
