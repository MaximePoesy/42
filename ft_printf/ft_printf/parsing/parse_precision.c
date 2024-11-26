/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:15:20 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/25 15:22:35 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	parse_precision(const char **str, int *flag)
{
	int	precision;

	precision = -1;
	if (**str == '.')
	{
		(*flag) |= FLAG_DOT;
		precision = 0;
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			precision = precision * 10 + (**str - '0');
			(*str)++;
		}
	}
	return (precision);
}
