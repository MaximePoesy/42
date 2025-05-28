/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:33:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 17:43:17 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(&philo->shared->write_lock);
	time = ts(philo->shared->start_time);
	printf("%ld %d%s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->shared->write_lock);
}
