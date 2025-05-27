/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:26:35 by staverni          #+#    #+#             */
/*   Updated: 2025/05/17 15:44:22 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strswap(char **a, char **b)
{
	char	*temp;

	if (a == NULL || b == NULL)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}
