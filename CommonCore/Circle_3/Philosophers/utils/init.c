/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:48:26 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 14:58:44 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	init(t_shared *shared, t_struct_args *args, t_philo *philos)
{
	int	i;

	shared->stop_simulation = 0;
	init_timestamp(&shared->start_time);
	shared->args = args;
	shared->philos = philos;
	shared->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!shared->forks)
		return (0);
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->write_lock, NULL);
	pthread_mutex_init(&shared->stop_lock, NULL);
	return (1);
}
