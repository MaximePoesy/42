/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:28:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 15:33:05 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	run_routine(t_philo *philo)
{
	while (!has_died(philo->shared))
	{
		if (philo->args->nb_times > 0
			&& get_meals_eaten(philo) >= philo->args->nb_times)
			break ;
		eat(philo);
		increment_meals_eaten(philo);
		usleep(100);
		if (has_died(philo->shared))
			break ;
		sleeping(philo);
		if (has_died(philo->shared))
			break ;
		think(philo);
		usleep(500);
	}
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_meals_eaten(philo, 0);
	if (philo->args->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->shared->forks[0]);
		print_action(philo, " has taken a fork");
		usleep(philo->args->time_to_die * 1000);
		pthread_mutex_unlock(&philo->shared->forks[0]);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		usleep(100);
	run_routine(philo);
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
		pthread_mutex_init(&philos[i].meals_eaten_lock, NULL);
		pthread_mutex_init(&philos[i].meal_lock, NULL);
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
	pthread_create(&sentinel_tid, NULL, sentinel_loop, &shared_args);
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	pthread_join(sentinel_tid, NULL);
	cleanup(args, shared_args);
	free(tid);
	free(philos);
}
