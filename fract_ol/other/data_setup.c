/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:20 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

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
