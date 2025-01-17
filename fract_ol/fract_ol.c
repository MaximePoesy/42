/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/17 11:06:06 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

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

// Return the number of interations needed to escape using the julia set
// Also change the output to better output low values using double log2
int	julia(double re, double im)
{
	double	num_re;
	double	num_im;
	double	temp_re;
	int		count;
	double	magnitude;

	num_re = re;
	num_im = im;
	count = 0;
	while (count < ITERATIONS_MAX)
	{
		temp_re = (num_re * num_re) - (num_im * num_im) + CONST_RE;
		num_im = (2 * num_re * num_im) + CONST_IM;
		num_re = temp_re;
		if ((num_re * num_re + num_im * num_im) > 4)
		{
			magnitude = sqrt(num_re * num_re + num_im * num_im);
			return (count + 1 - log2(log2(magnitude)));
		}
		count++;
	}
	return (ITERATIONS_MAX);
}

// Create a normalized version of the colors to better change the proportions of RGB
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

// First Map each pixel to the correct value in the complex plane
// Then get the Julia result
// Then Create smooth and better color
// Then set each pixel with the correct color
void	pixel_display_julia(t_data *data)
{
	int		x;
	int		y;
	int		index;
	double	re;
	double	im;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			re = (x - data->width / 2.0) * 4.0 / data->width;
			im = -(y - data->height / 2.0) * 4.0 / data->height;
			index = y * data->width + x;
			data->img_data[index] = create_color(julia(re, im));
			x++;
		}
		y++;
	}
}

// Mouse hook function
// Button == 1 is for left click
int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		pixel_display_julia(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
	return (0);
}

// Close the window and clean up
int	close_window(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
	return (0);
}

void	show_menu(void)
{
	ft_printf("-------------------------------------------------------------------------------\n");
	ft_printf("--------------------------------- FRACT_OL ------------------------------------\n");
	ft_printf("-------------------------------------------------------------------------------\n");
	ft_printf("\nUsage: ./fract_ol -j/-m CONST_RE CONST_IM\n\n");
	ft_printf("Usage: -j : Julia set\n\n");
	ft_printf("Usage: -m : Mandelbrot set\n\n");
	ft_printf("Usage: CONST_RE : Real part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("Usage: CONST_IM : Imaginary part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("-------------------------------------------------------------------------------\n");
        ft_printf("--------------------------------- FRACT_OL ------------------------------------\n");
        ft_printf("-------------------------------------------------------------------------------\n");
}

int	check_set(int argc, char **argv)
{
	char	str[10];

	if (argc != 4)
	{
		ft_printf("Wrong number of arguments.\n");
		show_menu();
		return (1);
	}
	if (ft_strcmp(argv[1], "-j") && ft_strcmp(argv[1], "-m"))
	{
		ft_printf("Wrong sets arguments\n");
		show_menu();
		return (1);
	}
	if (!ft_strcmp(argv[2], ft_ftoa(ft_atof(argv[2]), str, 10)) || !ft_strcmp(argv[3],
			ft_ftoa(ft_atof(argv[3]), str, 10)) || ft_strcmp(argv[2], "") || ft_strcmp(argv[3], ""))
	{
		ft_printf("Wrong arguments\n");
		show_menu();
		return (1);
	}
	return (0);
}

// Main function
// Creates the window
// Show the first image
// Define the hook to exit the window
// Define the hook to change the pixels
int	main(int argc, char **argv)
{
	t_data	data;

	if (check_set(argc, argv))
		return (0);

	init_window(&data, 1000, 1000, "fract_ol");
	if (ft_strcmp(argv[1], "-j"))
		pixel_display_julia(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, (int (*)(void *))close_window, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
