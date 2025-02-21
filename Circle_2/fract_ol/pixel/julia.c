/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:38 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:40 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

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
