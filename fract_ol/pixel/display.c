/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:37 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:38 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

//Loop to execute to each pixel the func
void	pixel_display(t_data *data)
{
	t_display	var;
	double		re;
	double		im;

	var.y = 0;
	while (var.y < data->height)
	{
		im = -((var.y - data->height / 2.0) * data->frac.s_im + data->ctr_im);
		var.x = 0;
		while (var.x < data->width)
		{
			re = (var.x - data->width / 2.0) * data->frac.s_re + data->ctr_re;
			var.index = var.y * data->width + var.x;
			if (data->julia == 0)
				data->img_data[var.index] = data->c.color[mand(re, im, data)];
			else if (data->julia == 1)
				data->img_data[var.index] = data->c.color[julia(re, im, data)];
			else
				data->img_data[var.index] = data->c.color[burn(re, im, data)];
			var.x++;
		}
		var.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
