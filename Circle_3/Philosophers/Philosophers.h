/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:43:42 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/27 17:31:57 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_struct_args
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times;
}					t_struct_args;

// stop_simulation is the actual value
// stop_lock is whether you shoudl read that value or not.
// It has no value by itself
typedef struct s_shared
{
	volatile int	stop_simulation;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
}					t_shared;

typedef struct s_philo
{
	int				id;
	t_struct_args	*args;
	t_shared		*shared;
}					t_philo;

int					valid_arg(const char *s, int *out);

#endif
