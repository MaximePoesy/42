/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_died.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:59:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/28 15:00:22 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	has_died(t_shared *shared)
{
	int	stop;

	pthread_mutex_lock(&shared->stop_lock);
	stop = shared->stop_simulation;
	pthread_mutex_unlock(&shared->stop_lock);
	return (stop);
}

void	set_stop(t_shared *shared)
{
	pthread_mutex_lock(&shared->stop_lock);
	shared->stop_simulation = 1;
	pthread_mutex_unlock(&shared->stop_lock);
}
