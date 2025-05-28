/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:28:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 18:12:16 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	sleeping(t_philo *philo)
{
	print_action(philo, " is sleeping");
	usleep(philo->args->time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	print_action(philo, " is thinking");
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->args->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->shared->forks[0]);
		print_action(philo, " has taken a fork");
		usleep(philo->args->time_to_die * 1000);
		pthread_mutex_unlock(&philo->shared->forks[0]);
		return (NULL);
	}
	philo->meals_eaten = 0;
	while (!has_died(philo->shared))
	{
		if ((philo->args->nb_times > 0
				&& philo->meals_eaten >= philo->args->nb_times)
			|| has_died(philo->shared))
			break ;
		eat(philo);
		philo->meals_eaten++;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static int	create_threads(t_philo *philos, pthread_t *tid, t_struct_args *args,
		t_shared *shared)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		philos[i].id = i;
		philos[i].args = args;
		philos[i].shared = shared;
		philos[i].last_meal = shared->start_time;
		if (pthread_create(&tid[i], NULL, philo_loop, &philos[i]))
			return (0);
		i++;
	}
	return (1);
}

void	start_loop(t_struct_args *args)
{
	int			i;
	t_shared	shared_args;
	pthread_t	*tid;
	t_philo		*philos;
	pthread_t	sentinel_tid;

	tid = malloc(sizeof(pthread_t) * args->nb_philo);
	philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!tid || !philos)
		return ;
	if (!init(&shared_args, args, philos))
		return ;
	if (!create_threads(philos, tid, args, &shared_args))
		return ;
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	pthread_create(&sentinel_tid, NULL, sentinel_loop, &shared_args);
	pthread_join(sentinel_tid, NULL);
	cleanup(args, shared_args);
	free(tid);
	free(philos);
}
