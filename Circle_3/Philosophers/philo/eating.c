/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:44:14 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 17:46:13 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	take_forks_even(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	pthread_mutex_lock(&philo->shared->forks[left]);
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(&philo->shared->forks[right]);
	print_action(philo, " has taken a fork");
}

static void	take_forks_odd(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	pthread_mutex_lock(&philo->shared->forks[right]);
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(&philo->shared->forks[left]);
	print_action(philo, " has taken a fork");
}

static void	release_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	pthread_mutex_unlock(&philo->shared->forks[left]);
	pthread_mutex_unlock(&philo->shared->forks[right]);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
	gettimeofday(&philo->last_meal, NULL);
	print_action(philo, " is eating");
	usleep(philo->args->time_to_eat * 1000);
	release_forks(philo);
}
