/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:27 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:12:30 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Create a normalized version of the colors to better
// change the proportions of RGB
int	create_color(double smooth_iteration)
{
	double	normalized;
	int		red;
	int		green;
	int		blue;

	normalized = smooth_iteration / (ITERATIONS_MAX * 0.5);
	if (normalized > 1.0)
		normalized = 1.0;
	else if (normalized < 0.0)
		normalized = 0.0;
	red = (int)(9 * (1 - normalized) * normalized * normalized * normalized
			* 255);
	green = (int)(15 * (1 - normalized) * (1 - normalized) * normalized
			* normalized * 255);
	blue = (int)(8.5 * (1 - normalized) * (1 - normalized) * (1 - normalized)
			* normalized * 255);
	return ((red << 16) | (green << 8) | blue);
}
