/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:20:32 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 11:29:22 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	get_meals_eaten(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->meals_eaten_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
	return (meals);
}

void	increment_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}

void	set_meals_eaten(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten = value;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}
