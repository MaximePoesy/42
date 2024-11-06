/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:44:39 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/04 16:23:11 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

unsigned char	char_to_ascii(unsigned char hex)
{
	if (hex < 10)
		return (hex + '0');
	else
		return (hex - 10 + 'a');
}

int	print_p(void *ptr)
{
	unsigned char	hex_digit;
	unsigned char	hex_addresses[16];
	unsigned long	address;
	int				index;
	int				shift;

	address = (unsigned long)ptr;
	index = 0;
	shift = 60;
	while (shift >= 0)
	{
		hex_digit = (address >> shift) & 0xF;
		hex_addresses[index++] = char_to_ascii(hex_digit);
		shift -= 4;
	}
	write(1, "0x", 2);
	write(1, hex_addresses, 16);
	return (18);
}
