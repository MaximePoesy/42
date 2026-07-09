/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:01:31 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 14:54:36 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	cleanup(t_struct_args *args, t_shared sharedArgs)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_destroy(&sharedArgs.forks[i]);
		pthread_mutex_destroy(&sharedArgs.philos[i].meal_lock);
		pthread_mutex_destroy(&sharedArgs.philos[i].meals_eaten_lock);
		i++;
	}
	pthread_mutex_destroy(&sharedArgs.stop_lock);
	pthread_mutex_destroy(&sharedArgs.write_lock);
	free(sharedArgs.forks);
}
