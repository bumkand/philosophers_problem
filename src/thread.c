/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:09:14 by jakand            #+#    #+#             */
/*   Updated: 2025/08/29 17:08:06 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*make_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = philo->data;
	while (1)
	{

		pthread_mutex_lock(&data->forks[philo->left_fork]);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
		printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
		printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		
		//printf("%lld %i is sleeping\n", time_in_ms() - data->start_time, philo->id);
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	philo_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = time_in_ms();
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_create(&data->philos[i].thread, NULL, make_routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}
