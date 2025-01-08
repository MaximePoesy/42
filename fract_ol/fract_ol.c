/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:11:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/08 14:31:07 by mpoesy           ###   ########.fr       */
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
/*
int	julia(double re, double im)
{
	double	num_re;
	double	num_im;
	double	temp_re;
	int		count;

	num_re = re;
	num_im = im;
	count = 0;
	while (count < ITERATIONS_MAX)
	{
		temp_re = (num_re * num_re) - (num_im * num_im) + CONST_RE;
		num_im = (2 * num_re * num_im) + CONST_IM;
		num_re = temp_re;
		count++;
		if ((num_re * num_re + num_im * num_im) > 4)
			break ;
	}
	return (count);
}

void	apply_red_tint(t_data *data)
{
	int		x;
	int		y;
	int		index;
	int		iteration;
	int		color;
	double	smooth_color;
	int		red;
	int		green;
	int		blue;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			iteration = julia((x - data->width / 2.0) * 4.0 / data->width, (y
						- data->height / 2.0) * 4.0 / data->height);
			smooth_color = iteration + 1.0 - log(log(sqrt(x * x + y * y)));
			color = (int)(smooth_color * 255.0 / ITERATIONS_MAX);
			red = (color * 255) / 256;
			green = (color * 150) / 256;
			blue = (color * 64) / 256;
			index = y * data->width + x;
			data->img_data[index] = (red << 16) | (green << 8) | blue;
			x++;
		}
		y++;
	}
}
*/

int     julia(double re, double im)
{
        double  num_re;
        double  num_im;
        double  temp_re;
        int             count;

        num_re = re;
        num_im = im;
        count = 0;
        while (count < ITERATIONS_MAX)
        {
                temp_re = (num_re * num_re) - (num_im * num_im) + CONST_RE;
                num_im = (2 * num_re * num_im) + CONST_IM;
                num_re = temp_re;
                count++;
                if ((num_re * num_re + num_im * num_im) > 4)
                        break ;
        }
        return (count);
}

void    apply_fractal_with_iterations(t_data *data, int iterations_to_show)
{
    int x, y, index, iteration;
    int red, green, blue;
    double smooth_color;

    y = 0;
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            // Adjust for the view and scale the coordinates to map them to the fractal space
            iteration = julia((x - data->width / 2.0) * 4.0 / data->width, 
                              (y - data->height / 2.0) * 4.0 / data->height);
            
            // Only show up to 'iterations_to_show' iterations
            if (iteration >= iterations_to_show)
                iteration = iterations_to_show;

            // Apply smooth color transition
            smooth_color = iteration + 1.0 - log(log(sqrt(x * x + y * y)));
            int color = (int)(smooth_color * 255.0 / ITERATIONS_MAX);

            // Create RGB values with a gradient
            red = (color * 255) / 256;
            green = (color * 150) / 256;
            blue = (color * 64) / 256;

            // Store the color value in the image data
            index = y * data->width + x;
            data->img_data[index] = (red << 16) | (green << 8) | blue;

            x++;
        }
        y++;
    }

    // Put the image data to the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

void    apply_red_tint(t_data *data)
{
    int iterations_to_show = 1;

    // Loop to incrementally display iterations
    while (iterations_to_show <= ITERATIONS_MAX)
    {
        mlx_clear_window(data->mlx_ptr, data->win_ptr);  // Clear the window
        apply_fractal_with_iterations(data, iterations_to_show);  // Apply fractal with limited iterations
        usleep(100000);  // Wait for a short period (100ms)

        iterations_to_show++;  // Increase iterations to show more details
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
