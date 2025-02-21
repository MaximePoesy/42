/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:12:57 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

// Initialize the mlx and window
void	init_window(t_data *data, int width, int height, char *title)
{
	data->width = width;
	data->height = height;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		perror("Error initializing mlx");
		exit(EXIT_FAILURE);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, title);
	if (!data->win_ptr)
	{
		perror("Error creating window");
		exit(EXIT_FAILURE);
	}
	data->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->img_ptr)
	{
		perror("Error creating image");
		exit(EXIT_FAILURE);
	}
	data->img_data = (int *)mlx_get_data_addr(data->img_ptr, &(int){0},
			&(int){0}, &(int){0});
}
