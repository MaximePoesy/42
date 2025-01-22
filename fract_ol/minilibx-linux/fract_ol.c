/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/22 17:00:28 by mpoesy           ###   ########.fr       */
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

// Return the number of interations needed to escape using the mandelbrot set
// Also change the output to better output low values using double log2
int	mand(double re, double im, t_data *data)
{
	double	num_re;
	double	num_im;
	double	temp_re;
	int		count;
	double	magnitude;

	(void)data;
	num_re = 0;
	num_im = 0;
	count = 0;
	while (count < ITERATIONS_MAX)
	{
		temp_re = (num_re * num_re) - (num_im * num_im) + re;
		num_im = (2 * num_re * num_im) + im;
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

double	abs_value(double n)
{
	if (n < 0)
		n = -n;
	return (n);
}

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
		zy = 2 * abs_value(zx) * abs_value(zy) + y;
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

// Return the number of interations needed to escape using the julia set
// Also change the output to better output low values using double log2
int	julia(double re, double im, t_data *data)
{
	double	num_re;
	double	num_im;
	double	temp_re;
	int		count;
	t_num	num;

	num_re = re;
	num_im = im;
	count = 0;
	while (count < ITERATIONS_MAX)
	{
		num.re_sq = num_re * num_re;
		num.im_sq = num_im * num_im;
		if (num.re_sq + num.im_sq > 4.0)
			return (count + 1 - log2(0.5 * log2(num.re_sq + num.im_sq)));
		temp_re = num.re_sq - num.im_sq + data->const_re;
		num_im = 2 * num_re * num_im + data->const_im;
		num_re = temp_re;
		count++;
	}
	return (ITERATIONS_MAX);
}

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

void	pixel_display(t_data *data)
{
	t_display	var;
	double		re;
	double		im;

	var.y = 0;
	while (var.y < data->height)
	{
		im = -(var.y - data->height / 2.0) * data->frac.s_im + data->ctr_im;
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

// Close the window and clean up
int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

// Mouse hook function
// KEY_LEFT 123
// KEY_RIGHT 124
// KEY_DOWN 125
// KEY_UP 126
// keycode == 65307 is for Esc key
int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->ctr_re -= MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_RIGHT)
		data->ctr_re += MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_UP)
		data->ctr_im += MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_DOWN)
		data->ctr_im -= MOVE_SPEED / data->zoom_level;
	else if (keycode == 65307)
		close_window(data);
	pixel_display(data);
	return (0);
}

// Menu in case of wrong parameters
void	show_menu(void)
{
	ft_printf("-------------------------------------------------------\n");
	ft_printf("--------------------- FRACT_OL ------------------------\n");
	ft_printf("-------------------------------------------------------\n");
	ft_printf("\nUsage: ./fract_ol -j/-m/-b CONST_RE CONST_IM\n\n");
	ft_printf("Usage: -j : Julia set\n\n");
	ft_printf("Usage: -m : Mandelbrot set\n\n");
	ft_printf("Usage: -b : Burning ship set\n\n");
	ft_printf("Usage: CONST_RE : Real part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("Usage: CONST_IM : Imaginary part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("-------------------------------------------------------\n");
	ft_printf("--------------------- FRACT_OL ------------------------\n");
	ft_printf("-------------------------------------------------------\n");
}

// Verify that the parameters called with the function are correct
int	check_set(int argc, char **argv)
{
	if (argc != 4)
	{
		ft_printf("\nWrong number of arguments.\n");
		show_menu();
		return (1);
	}
	if (ft_strcmp(argv[1], "-j") && ft_strcmp(argv[1], "-m") && ft_strcmp(argv[1], "-b"))
	{
		ft_printf("\nWrong sets arguments\n");
		show_menu();
		return (1);
	}
	if (!ft_is_float(argv[2]) || !ft_is_float(argv[3]))
	{
		ft_printf("\nWrong arguments\n");
		show_menu();
		return (1);
	}
	return (0);
}

void	zoom(t_data *data, int x, int y, double factor)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = (x - data->width / 2.0) * (4.0 / data->width) / data->zoom_level
		+ data->ctr_re;
	mouse_im = -(y - data->height / 2.0) * (4.0 / data->height)
		/ data->zoom_level + data->ctr_im;
	data->zoom_level *= factor;
	data->ctr_re += (mouse_re - data->ctr_re) * (1 - 1 / factor);
	data->ctr_im += (mouse_im - data->ctr_im) * (1 - 1 / factor);
	data->frac.s_re = 4.0 / data->width / data->zoom_level;
	data->frac.s_im = 4.0 / data->height / data->zoom_level;
	pixel_display(data);
}

// 4 : Wheel up
// 5 : Wheel down
int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
		zoom(data, x, y, ZOOM_IN_FACTOR);
	else if (button == 5)
		zoom(data, x, y, ZOOM_OUT_FACTOR);
	return (0);
}

void	data_setup(t_data *data, int julia, char *argv2, char *argv3)
{
	int	i;

	data->ctr_re = 0;
	data->ctr_im = 0;
	data->zoom_level = 1;
	data->frac.s_re = 4.0 / data->width / data->zoom_level;
	data->frac.s_im = 4.0 / data->height / data->zoom_level;
	data->const_re = ft_atof(argv2);
	data->const_im = ft_atof(argv3);
	data->julia = julia;
	data->color_shift = 0;
	i = 0;
	while (i < ITERATIONS_MAX)
	{
		precompute_colors(data);
		i++;
	}
}

int	color_shift(t_data *data)
{
	int			pixel_index;
	static int	frame_count = 0;

	int color, red, green, blue;
	frame_count++;
	if (frame_count > 6000)
	{
		frame_count = 0;
		data->color_shift = (data->color_shift + 1) % ITERATIONS_MAX;
		pixel_index = 0;
		while (pixel_index < data->width * data->height)
		{
			color = data->img_data[pixel_index];
			// color = (color + 0x000001) % 0xFFFFFF;
			red = (color >> 16) & 0xFF;
			green = (color >> 8) & 0xFF;
			blue = color & 0xFF;
			// Gradually increment each color channel
			red = (red + 7) % 256;      // Wrap around after reaching 255
			green = (green + 13) % 256; // Wrap around after reaching 255
			blue = (blue + 19) % 256;   // Wrap around after reaching 255
			// Reassemble the color
			color = (red << 16) | (green << 8) | blue;
			data->img_data[pixel_index] = color;
			pixel_index++;
		}
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
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
	init_window(&data, 500, 500, "fract_ol");
	if (!ft_strcmp(argv[1], "-j"))
	{
		data_setup(&data, 1, argv[2], argv[3]);
		pixel_display(&data);
	}
	else if (!ft_strcmp(argv[1], "-m"))
	{
		data_setup(&data, 0, argv[2], argv[3]);
		pixel_display(&data);
	}
	else if(!ft_strcmp(argv[1], "-j"))
	{
		data_setup(&data, 2, argv[2], argv[3]);
                pixel_display(&data);
	}
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, (int (*)(void *))close_window, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop_hook(data.mlx_ptr, color_shift, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
