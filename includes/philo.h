/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:56:56 by jakand            #+#    #+#             */
/*   Updated: 2025/08/31 16:30:23 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_ate;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	int				everyone_ate;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
}	t_data;

int	init_data(t_data *data, int arc, char *arv[]);

int	philo_threads(t_data *data);

long long	time_in_ms(void);

int	ft_atoi(const char *nptr);

#endif
