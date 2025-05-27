/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:50:38 by staverni          #+#    #+#             */
/*   Updated: 2025/03/11 17:29:24 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	case_p(const void *p)
{
	uintptr_t	addr;
	char		hex_number[17];
	int			i;

	i = 15;
	addr = (uintptr_t)p;
	hex_number[16] = '\0';
	if (addr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		while (addr > 0 || i == 15)
		{
			hex_number[i--] = HEX_SET[addr & 0xF];
			addr >>= 4;
		}
		i++;
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(&hex_number[i], 1);
	}
	return (ft_strlen(&hex_number[i]) + 2);
}
