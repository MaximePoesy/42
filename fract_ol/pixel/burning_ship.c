/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:35 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:37 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	burn(double x, double y, t_data *data)
{
	double	zx;
	double	zy;
	double	tmp;
	double	magnitude;
	int		iteration;

	(void)data;
	zx = 0;
	zy = 0;
	iteration = 0;
	while (iteration < ITERATIONS_MAX)
	{
		tmp = zx * zx - zy * zy + x;
		zy = 2 * abs_value(zx) * abs_value(zy) - y;
		zx = abs_value(tmp);
		if (zx * zx + zy * zy > 4)
		{
			magnitude = sqrt(zx * zx + zy * zy);
			return (iteration + 1 - log2(log2(magnitude)));
		}
		iteration++;
	}
	return (ITERATIONS_MAX);
}
