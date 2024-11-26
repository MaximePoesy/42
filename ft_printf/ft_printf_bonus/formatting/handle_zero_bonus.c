/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:51:47 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/25 11:19:27 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	handle_zero(t_format *format)
{
	int		width;
	int		num_char;
	char	pad_char;

	num_char = 0;
	if (format->width > 0)
		width = format->width;
	else
		width = 1;
	if (format->flags & FLAG_MINUS)
	{
		write(1, "\0", 1);
		while (num_char++ < width - 1)
			write(1, " ", 1);
	}
	else
	{
		if (format->flags & FLAG_ZERO)
			pad_char = '0';
		else
			pad_char = ' ';
		while (num_char < width - 1)
		{
			write(1, &pad_char, 1);
			num_char++;
		}
		write(1, "\0", 1);
		num_char++;
	}
	return (num_char);
}
