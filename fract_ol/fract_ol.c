/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/07 17:29:46 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

void	apply_red_tint(t_data *data)
{
	int	index;
	int	color;
	int	red;
	int	green;
	int	blue;

	for (int y = 0; y < data->height; y++)
	{
		for (int x = 0; x < data->width; x++)
		{
			index = y * data->width + x;
			color = data->img_data[index];
			red = (color & 0xFF0000) >> 16;
			green = (color & 0x00FF00) >> 8;
			blue = color & 0x0000FF;
			red = (red + 50) % 256;
			data->img_data[index] = (red << 16) | (green << 8) | blue;
		}
	}
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		apply_red_tint(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.width = 500;
	data.height = 500;
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height,
			"fract_ol");
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.img_data = (int *)mlx_get_data_addr(data.img_ptr, &(int){0}, &(int){0},
			&(int){0});
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
