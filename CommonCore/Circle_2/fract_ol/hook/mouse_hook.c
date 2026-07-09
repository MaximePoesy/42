/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:12:43 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:12:45 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

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
