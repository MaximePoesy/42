/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:08:34 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/27 11:40:34 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	parse_args(args_struct args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (!valid_arg(argv[1], &a->nb_philo))
		return (1);
	if (!valid_arg(argv[2], &a->time_to_die))
		return (1);
	if (!valid_arg(argv[3], &a->time_to_eat))
		return (1);
	if (!valid_arg(argv[4], &a->time_to_sleep))
		return (1);
	if (argc == 6 && !valid_arg(argv[5], &a->nb_times))
		return (1);
	if (argc == 5)
		a->nb_times = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct_args	args;

	if (argc != 4 || argc != 5)
	{
		printf("Wrong number of arguments\n");
		printf("Arguments :\n");
		printf("number_of_philosophers\ntime_to_die\ntime_to_eat\n");
		printf("time_to_sleep\n[number_of_times_each_philosopher_must_eat]");
	}
	if (!parse_args(args, argc, argv))
	{
		printf("Error parsing arguments\n");
		return (0);
	}
	start_loop(&args);
	return (0);
}
