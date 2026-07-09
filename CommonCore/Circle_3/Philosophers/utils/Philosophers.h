/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:43:42 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/03 15:31:23 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_struct_args
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times;
}						t_struct_args;

typedef struct s_philo	t_philo;

// stop_simulation is the actual value
// stop_lock is whether you shoudl read that value or not.
// It has no value by itself
typedef struct s_shared
{
	volatile int		stop_simulation;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	struct timeval		start_time;
	t_struct_args		*args;
	t_philo				*philos;
}						t_shared;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		meals_eaten_lock;
	int					meals_eaten;
	t_struct_args		*args;
	t_shared			*shared;
	pthread_mutex_t		meal_lock;
	struct timeval		last_meal;
}						t_philo;

int						valid_arg(const char *s, int *out);
int						init(t_shared *shared, t_struct_args *args,
							t_philo *philos);
long					ts(struct timeval start);
void					init_timestamp(struct timeval *start_time);
void					start_loop(t_struct_args *args);
void					cleanup(t_struct_args *args, t_shared sharedArgs);
void					*sentinel_loop(void *sharedPtr);
void					eat(t_philo *philo);
void					think(t_philo *philo);
void					sleeping(t_philo *philo);
void					set_stop(t_shared *shared);
int						has_died(t_shared *shared);
void					print_action(t_philo *philo, char *action);
int						get_meals_eaten(t_philo *philo);
void					increment_meals_eaten(t_philo *philo);
void					set_meals_eaten(t_philo *philo, int value);

#endif
