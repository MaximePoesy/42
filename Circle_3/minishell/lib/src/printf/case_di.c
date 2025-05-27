/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:59:20 by staverni          #+#    #+#             */
/*   Updated: 2025/03/11 17:29:24 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	case_di(int n)
{
	char	*p;
	size_t	length;

	p = ft_itoa(n);
	if (!p)
		return (0);
	ft_putstr_fd(p, 1);
	length = ft_strlen(p);
	free(p);
	return (length);
}
