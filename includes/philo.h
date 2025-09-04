/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:56:56 by jakand            #+#    #+#             */
/*   Updated: 2025/09/04 20:56:39 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_ate;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long long		philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_of_eats;
	int				everyone_ate;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	print;
}					t_data;

int					init_data(t_data *data, int arc, char *arv[]);

int					philo_threads(t_data *data);

int					eating_action(t_data *data, t_philo *philo);

int					odd_philosophers(t_data *data, t_philo *philo);

int					even_philosophers(t_data *data, t_philo *philo);

int					sleep_and_think(t_data *data, t_philo *philo);

void				*monitor_actions(void *arg);

long long			time_in_ms(void);

long long			ft_atoi(const char *nptr);

void				free_data(t_data *data);

#endif
