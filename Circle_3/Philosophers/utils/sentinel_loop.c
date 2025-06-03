/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentinel_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:58:04 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 15:32:22 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	philo_died(t_shared *shared, int i)
{
	long	elapsed;
	int		nb_times;

	pthread_mutex_lock(&shared->philos[i].meal_lock);
	elapsed = ts(shared->philos[i].last_meal);
	pthread_mutex_unlock(&shared->philos[i].meal_lock);
	nb_times = shared->args->nb_times;
	if (elapsed > shared->args->time_to_die && (nb_times == -1
			|| get_meals_eaten(&shared->philos[i]) < nb_times))
	{
		print_action(&shared->philos[i], " died");
		return (1);
	}
	return (0);
}

static int	all_philos_finished(t_shared *shared)
{
	int	i;
	int	nb_philo;
	int	nb_times;

	nb_philo = shared->args->nb_philo;
	nb_times = shared->args->nb_times;
	if (nb_times == -1)
		return (0);
	i = 0;
	while (i < nb_philo)
	{
		if (get_meals_eaten(&shared->philos[i]) < nb_times)
			return (0);
		i++;
	}
	return (1);
}

void	*sentinel_loop(void *arg)
{
	t_shared	*shared;
	int			i;

	shared = (t_shared *)arg;
	while (1)
	{
		i = 0;
		while (i < shared->args->nb_philo)
		{
			if (philo_died(shared, i))
			{
				set_stop(shared);
				return (NULL);
			}
			i++;
		}
		if (all_philos_finished(shared))
		{
			set_stop(shared);
			return (NULL);
		}
		usleep(1000);
	}
}
