/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:01:31 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 10:03:02 by mpoesy           ###   ########.fr       */
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
		i++;
	}
	pthread_mutex_destroy(&sharedArgs.stop_lock);
	free(sharedArgs.forks);
}
