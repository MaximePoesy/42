/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:48:38 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/12 12:51:34 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_add_value(t_vec3 a, int value)
{
	a.x = a.x + value;
	a.y = a.y + value;
	a.z = a.z + value;
	return (a);
}
