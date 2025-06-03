/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:44:14 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 11:08:46 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	take_forks_even(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	pthread_mutex_lock(&philo->shared->forks[left]);
	if (has_died(philo->shared))
	{
		pthread_mutex_unlock(&philo->shared->forks[left]);
		return (0);
	}
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(&philo->shared->forks[right]);
	if (has_died(philo->shared))
	{
		pthread_mutex_unlock(&philo->shared->forks[right]);
		pthread_mutex_unlock(&philo->shared->forks[left]);
		return (0);
	}
	print_action(philo, " has taken a fork");
	return (1);
}

static int	take_forks_odd(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->args->nb_philo;
	pthread_mutex_lock(&philo->shared->forks[right]);
	if (has_died(philo->shared))
	{
		pthread_mutex_unlock(&philo->shared->forks[right]);
		return (0);
	}
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(&philo->shared->forks[left]);
	if (has_died(philo->shared))
	{
		pthread_mutex_unlock(&philo->shared->forks[left]);
		pthread_mutex_unlock(&philo->shared->forks[right]);
		return (0);
	}
	print_action(philo, " has taken a fork");
	return (1);
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
	int	success;

	if (philo->id % 2 == 0)
		success = take_forks_even(philo);
	else
		success = take_forks_odd(philo);
	if (!success)
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, " is eating");
	usleep(philo->args->time_to_eat * 1000);
	release_forks(philo);
}
