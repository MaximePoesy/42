/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:31 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:14:03 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Precompute colors for iteration counts
void	precompute_colors(t_data *data)
{
	int	i;

	i = 0;
	while (i < ITERATIONS_MAX + 1)
	{
		data->c.color[i] = create_color((double)i);
		i++;
	}
}
