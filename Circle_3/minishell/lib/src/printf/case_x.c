/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:36 by staverni          #+#    #+#             */
/*   Updated: 2025/03/11 17:29:24 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	case_x(unsigned int n, const char c)
{
	char	hex_number[17];
	int		i;

	i = 15;
	hex_number[16] = '\0';
	if (n == 0)
		hex_number[i--] = '0';
	while (n > 0 || i == 15)
	{
		if (c == 'X')
			hex_number[i--] = ft_toupper(HEX_SET[n & 0xF]);
		else
			hex_number[i--] = HEX_SET[n & 0xF];
		n >>= 4;
	}
	i++;
	ft_putstr_fd(&hex_number[i], 1);
	return (ft_strlen(&hex_number[i]));
}
