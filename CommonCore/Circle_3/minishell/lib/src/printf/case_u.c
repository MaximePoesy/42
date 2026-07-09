/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:05:26 by staverni          #+#    #+#             */
/*   Updated: 2025/03/11 17:29:24 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	case_u(const unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += case_u(n / 10);
		count += case_u(n % 10);
	}
	else
	{
		ft_putchar_fd(n + '0', 1);
		count++;
	}
	return (count);
}
