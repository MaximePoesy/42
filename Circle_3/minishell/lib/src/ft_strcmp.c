/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:40:02 by staverni          #+#    #+#             */
/*   Updated: 2025/03/25 13:40:43 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *p1, const char *p2)
{
	while (*p1 && (*p1 == *p2))
	{
		p1++;
		p2++;
	}
	return ((unsigned char)*p1 - (unsigned char)*p2);
}
