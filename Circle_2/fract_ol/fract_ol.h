/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:27:45 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/21 17:00:54 by mpoesy           ###   ########.fr       */
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

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define MOVE_SPEED 0.1

# define FRAME_COUNT 5000
# define HEIGHT 700
# define WIDTH 700

# ifndef ITERATIONS_MAX
#  define ITERATIONS_MAX 500
# endif

# ifndef ZOOM_IN_FACTOR
#  define ZOOM_IN_FACTOR 1.2
# endif
# ifndef ZOOM_OUT_FACTOR
#  define ZOOM_OUT_FACTOR 0.8
# endif

typedef struct s_num
{
	double		re_sq;
	double		im_sq;
}				t_num;

typedef struct s_col
{
	int			color[ITERATIONS_MAX + 1];
}				t_col;

// s for scale
// to scale the window correctl
// better to use a struct to not have to calculate it several times for nothing
typedef struct s_fractal
{
	double		s_re;
	double		s_im;
}				t_fractal;

// julia = 1 -> julia
// julia = 0 -> mandelbrot
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_data;
	int			width;
	int			height;
	double		zoom_level;
	double		ctr_re;
	double		ctr_im;
	double		const_re;
	double		const_im;
	int			julia;
	t_fractal	frac;
	t_col		c;
	int			color_shift;
}				t_data;

typedef struct s_display
{
	int			x;
	int			y;
	int			index;
}				t_display;

int				color_shift(t_data *data);
int				create_color(double smooth_iteration);
void			precompute_colors(t_data *data);
int				key_hook(int keycode, t_data *data);
int				mouse_hook(int button, int x, int y, t_data *data);
int				close_window(t_data *data);
void			init_window(t_data *data, int width, int height, char *title);
double			abs_value(double n);
int				check_set(int argc, char **argv);
void			data_setup(t_data *data, int julia, char *argv2, char *argv3);
void			show_menu(void);
int				burn(double x, double y, t_data *data);
void			pixel_display(t_data *data);
int				julia(double re, double im, t_data *data);
int				mand(double re, double im, t_data *data);
void			zoom(t_data *data, int x, int y, double factor);
#endif
