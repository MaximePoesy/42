/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:16 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/28 14:13:19 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// Verify that the parameters called with the function are correct
int	check_set(int argc, char **argv)
{
	if (argc != 4)
	{
		ft_printf("\nWrong number of arguments.\n");
		show_menu();
		return (1);
	}
	if (ft_strcmp(argv[1], "-j") && ft_strcmp(argv[1], "-m")
		&& ft_strcmp(argv[1], "-b"))
	{
		ft_printf("\nWrong sets arguments\n");
		show_menu();
		return (1);
	}
	if (!ft_is_float(argv[2]) || !ft_is_float(argv[3]))
	{
		ft_printf("\nWrong arguments\n");
		show_menu();
		return (1);
	}
	return (0);
}
