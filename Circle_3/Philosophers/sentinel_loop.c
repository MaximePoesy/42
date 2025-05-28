/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentinel_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:58:04 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 18:08:55 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	philo_died(t_shared *shared, int i)
{
	long	elapsed;
	int		nb_times;

	elapsed = ts(shared->philos[i].last_meal);
	nb_times = shared->args->nb_times;
	if (elapsed > shared->args->time_to_die && (nb_times == -1
			|| shared->philos[i].meals_eaten < nb_times))
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
		if (shared->philos[i].meals_eaten < nb_times)
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
	i = 0;
	while (1)
	{
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
