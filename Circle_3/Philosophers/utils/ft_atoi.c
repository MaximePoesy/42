/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:03 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/27 11:28:15 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	str_to_int(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!str || !*str)
		return (-1);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	valid_arg(const char *s, int *out)
{
	int	n;

	n = str_to_int(s);
	if (n <= 0)
		return (0);
	*out = n;
	return (1);
}
