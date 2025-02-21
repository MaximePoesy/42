/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:21 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:24 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Menu in case of wrong parameters
void	show_menu(void)
{
	ft_printf("-------------------------------------------------------\n");
	ft_printf("--------------------- FRACT_OL ------------------------\n");
	ft_printf("-------------------------------------------------------\n");
	ft_printf("\nUsage: ./fract_ol -j/-m/-b CONST_RE CONST_IM\n\n");
	ft_printf("Usage: -j : Julia set\n\n");
	ft_printf("Usage: -m : Mandelbrot set\n\n");
	ft_printf("Usage: -b : Burning ship set\n\n");
	ft_printf("Usage: CONST_RE : Real part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("Usage: CONST_IM : Imaginary part of the constant");
	ft_printf(" implemented as float\n");
	ft_printf("May only be 10 characters max\n\n");
	ft_printf("-------------------------------------------------------\n");
	ft_printf("--------------------- FRACT_OL ------------------------\n");
	ft_printf("-------------------------------------------------------\n");
}
