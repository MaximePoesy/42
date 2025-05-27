/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:28:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/27 17:54:47 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->shared->forks[left]);
		printf("%ld %d has taken a fork\n",
			timestamp(philo->shared->start_time), philo->id + 1);
		pthread_mutex_lock(&philo->shared->forks[right]);
		printf("%ld %d has taken a fork\n",
			timestamp(philo->shared->start_time), philo->id + 1);
	}
	else
	{
		pthread_mutex_lock(&philo->shared->forks[right]);
		printf("%ld %d has taken a fork\n",
			timestamp(philo->shared->start_time), philo->id + 1);
		pthread_mutex_lock(&philo->shared->forks[left]);
		printf("%ld %d has taken a fork\n",
			timestamp(philo->shared->start_time), philo->id + 1);
	}
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->shared->forks[left]);
	pthread_mutex_unlock(&philo->shared->forks[right]);
}

static void	sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", timestamp(philo->shared->start_time),
		philo->id + 1);
	usleep(philo->args->time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", timestamp(philo->shared->start_time),
		philo->id + 1);
	usleep(philo->args->time_to_sleep * 1000);
}

void	*philo_loop(void *sharedArgs)
{
	t_philo			*philo;
	t_shared		*shared;
	t_struct_args	*args;

	philo = (t_philo *)arg;
	shared = philo->shared;
	args = philo->args;
	shared = (t_shared *)arg;
	while (1)
	{
		pthread_mutex_lock(&shared->stop_lock);
		if (shared->stop_simulation)
		{
			pthread_mutex_unlock(&shared->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&shared->stop_lock);
		eat(args->time_to_sleep);
		sleep(args->time_to_sleep);
		think(arg);
	}
	return (NULL);
}

void	start_loop(t_struct_args *args)
{
	int			i;
	t_shared	sharedArgs;
	pthread_t	tid[args->nb_philo];
	t_philo		philos[args->nb_philo];

	shared.stop_simulation = 0;
	i = 0;
	init_timestamp(&sharedArgs.start_time);
	while (i < args->nb_philo)
	{
		philos[i].id = i;
		philos[i].args = args;
		philos[i].shared = &sharedArgs;
		phtread_create(&tid[i], NULL, philo_loop, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		phtread_join(tid[i], NULL);
		i++;
	}
}
