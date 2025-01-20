/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:27:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/20 17:50:02 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef ITERATIONS_MAX
#  define ITERATIONS_MAX 400
# endif

#define ZOOM_IN_FACTOR 1.2
#define ZOOM_OUT_FACTOR 0.8

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_data;
	int		width;
	int		height;
	double	zoom_level;
	double	center_re;
	double	center_im;
	double	const_re;
	double	const_im;
}			t_data;

#endif
