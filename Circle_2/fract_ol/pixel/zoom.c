/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:41 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:46 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	zoom(t_data *data, int x, int y, double factor)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = (x - data->width / 2.0) * (4.0 / data->width) / data->zoom_level
		+ data->ctr_re;
	mouse_im = (y - data->height / 2.0) * (4.0 / data->height)
		/ data->zoom_level + data->ctr_im;
	data->zoom_level *= factor;
	data->ctr_re += (mouse_re - data->ctr_re) * (1 - 1 / factor);
	data->ctr_im += (mouse_im - data->ctr_im) * (1 - 1 / factor);
	data->frac.s_re = 4.0 / data->width / data->zoom_level;
	data->frac.s_im = 4.0 / data->height / data->zoom_level;
	pixel_display(data);
}
