/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:27:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/08 14:31:45 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>

#ifndef ITERATIONS_MAX
# define ITERATIONS_MAX 10
#endif

#ifndef CONST_RE
# define CONST_RE 0.5
#endif

#ifndef CONST_IM
# define CONST_IM 0.5
#endif

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_data;
	int		width;
	int		height;
}			t_data;

#endif
