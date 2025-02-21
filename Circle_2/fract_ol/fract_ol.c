/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:17:05 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Main function
// Creates the window
// Show the first image
// Define the hook to exit the window
// Define the hook to change the pixels
int	main(int argc, char **argv)
{
	t_data	data;
	int		fractal_type;

	if (check_set(argc, argv))
		return (0);
	init_window(&data, 500, 500, "fract_ol");
	if (!ft_strcmp(argv[1], "-j"))
		fractal_type = 1;
	else if (!ft_strcmp(argv[1], "-m"))
		fractal_type = 0;
	else if (!ft_strcmp(argv[1], "-b"))
		fractal_type = 2;
	else
		return (0);
	data_setup(&data, fractal_type, argv[2], argv[3]);
	pixel_display(&data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, (int (*)(void *))close_window, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop_hook(data.mlx_ptr, color_shift, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
