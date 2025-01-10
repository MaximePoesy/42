/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/10 16:14:50 by mpoesy           ###   ########.fr       */
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

int julia(double re, double im)
{
    double num_re = re;
    double num_im = im;
    double temp_re;
    int count = 0;

    while (count < ITERATIONS_MAX)
    {
        temp_re = (num_re * num_re) - (num_im * num_im) + CONST_RE;
        num_im = (2 * num_re * num_im) + CONST_IM;
        num_re = temp_re;

        if ((num_re * num_re + num_im * num_im) > 4)
        {
            double magnitude = sqrt(num_re * num_re + num_im * num_im);
            return count + 1 - log2(log2(magnitude));
        }
        count++;
    }
    return ITERATIONS_MAX;
}

int create_color(double smooth_iteration)
{
    double normalized = smooth_iteration / ITERATIONS_MAX;

    // Ensure normalization stays in range [0, 1]
    if (normalized > 1.0)
        normalized = 1.0;
    else if (normalized < 0.0)
        normalized = 0.0;

    // Gradient color mapping
    int red = (int)(9 * (1 - normalized) * normalized * normalized * normalized * 255);
    int green = (int)(15 * (1 - normalized) * (1 - normalized) * normalized * normalized * 255);
    int blue = (int)(8.5 * (1 - normalized) * (1 - normalized) * (1 - normalized) * normalized * 255);

    return (red << 16) | (green << 8) | blue;
}

void apply_red_tint(t_data *data)
{
    int x, y, index, color;
    double re, im, smooth_iter;

    y = 0;
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            // Map pixel (x, y) to complex plane
            re = (x - data->width / 2.0) * 4.0 / data->width;
            im = (y - data->height / 2.0) * 4.0 / data->height;

            // Get smooth iteration value
            smooth_iter = julia(re, im);

            // Create color based on smooth iteration
            color = create_color(smooth_iter);

            // Set pixel color
            index = y * data->width + x;
            data->img_data[index] = color;
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
		apply_red_tint(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
	return (0);
}

// Close the window and clean up
int	close_window(t_data *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

// Main function
// Creates the window
// Show the first image
// Define the hook to exit the window
// Define the hook to change the pixels
int	main(void)
{
	t_data	data;

	init_window(&data, 1000, 1000, "fract_ol");
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, (int (*)(void *))close_window, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
