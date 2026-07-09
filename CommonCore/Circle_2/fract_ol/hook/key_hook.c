/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:41 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:12:43 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Mouse hook function
// MOVE_SPEED = 0.1 by default
// KEY_LEFT 65361
// KEY_RIGHT 65363
// KEY_DOWN 65364
// KEY_UP 65362
// keycode == 65307 is for Esc key
int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->ctr_re -= MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_RIGHT)
		data->ctr_re += MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_UP)
		data->ctr_im -= MOVE_SPEED / data->zoom_level;
	else if (keycode == KEY_DOWN)
		data->ctr_im += MOVE_SPEED / data->zoom_level;
	else if (keycode == 65307)
		close_window(data);
	pixel_display(data);
	return (0);
}
