/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:56:32 by staverni          #+#    #+#             */
/*   Updated: 2025/03/11 17:29:24 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cases(const char c, va_list list)
{
	if (c == 'c')
		return (case_c(va_arg(list, int)));
	else if (c == 'd' || c == 'i')
		return (case_di(va_arg(list, int)));
	else if (c == 'p')
		return (case_p(va_arg(list, void *)));
	else if (c == 's')
		return (case_s(va_arg(list, char *)));
	else if (c == 'u')
		return (case_u(va_arg(list, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (case_x(va_arg(list, unsigned int), c));
	else if (c == '%')
		return (case_c('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		count;

	if (!str)
		return (-1);
	va_start(list, str);
	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		else
		{
			str++;
			count += cases(*str, list);
		}
		str++;
	}
	va_end(list);
	return (count);
}
