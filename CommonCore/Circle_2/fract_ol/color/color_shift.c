/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:21 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/21 16:59:37 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Function to handle the color shift for all pixels
static void	process_color_shift(t_data *data)
{
	int	pixel_index;
	int	color;
	int	red;
	int	green;
	int	blue;

	pixel_index = 0;
	while (pixel_index < data->width * data->height)
	{
		color = data->img_data[pixel_index];
		red = (color >> 16) & 0xFF;
		green = (color >> 8) & 0xFF;
		blue = color & 0xFF;
		red = (red + 7) % 256;
		green = (green + 13) % 256;
		blue = (blue + 19) % 256;
		data->img_data[pixel_index] = (red << 16) | (green << 8) | blue;
		pixel_index++;
	}
}

// Main color shift function
int	color_shift(t_data *data)
{
	static int	frame_count = 0;

	if (++frame_count > FRAME_COUNT && data->julia == 1)
	{
		frame_count = 0;
		data->color_shift = (data->color_shift + 1) % ITERATIONS_MAX;
		process_color_shift(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
	return (0);
}
