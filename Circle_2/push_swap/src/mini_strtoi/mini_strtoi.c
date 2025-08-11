/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_strtoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:59:28 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 09:59:30 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_strtoi.h"

static void	handle_negative(int *p_number, int digit)
{
	if ((*p_number > INT_MAX / 10) || ((*p_number == INT_MAX / 10)
			&& (digit > INT_MAX % 10)))
		display_err_exit();
	*p_number = (*p_number * 10) + digit;
}

static void	handle_positive(int *p_number, int digit)
{
	if ((*p_number < INT_MIN / 10) || ((*p_number == INT_MIN / 10)
			&& (digit > (INT_MIN % 10) * -1)))
		display_err_exit();
	*p_number = (*p_number * 10) - digit;
}

int	mini_strtoi(const char *str)
{
	bool	is_negative;
	int		number;

	is_negative = false;
	if (*str == '-')
	{
		is_negative = true;
		str++;
	}
	number = 0;
	if (*str == '\0')
		display_err_exit();
	while (*str)
	{
		if (!ft_isdigit(*str))
			display_err_exit();
		if (!is_negative)
			handle_negative(&number, *str - '0');
		else
			handle_positive(&number, *str - '0');
		str++;
	}
	return (number);
}
