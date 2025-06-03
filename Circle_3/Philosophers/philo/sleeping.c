/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:15:21 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 09:18:55 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	sleeping(t_philo *philo)
{
	print_action(philo, " is sleeping");
	usleep(philo->args->time_to_sleep * 1000);
}
