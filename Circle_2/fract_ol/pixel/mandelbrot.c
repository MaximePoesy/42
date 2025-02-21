/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:40 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:41 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

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
