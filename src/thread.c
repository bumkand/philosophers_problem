/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:09:14 by jakand            #+#    #+#             */
/*   Updated: 2025/09/01 20:46:57 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_actions(void *arg)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *) arg;
	i = 0;
	while (i < philo->data->philo_num && !philo->data->stop)
	{
		if (time_in_ms() - philo[i].last_meal_time > philo->data->time_to_die)
		{
			printf("%lld %d died\n\n\n\n\n\n", time_in_ms() - philo->data->start_time, philo[i].id);
			philo->data->stop = 1;
			return (NULL);
		}
		usleep(100);
		i++;
		if (i == philo->data->philo_num)
			i = 0;
	}
	return (NULL);
}

int	eating_action(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	
	if (data->philo_num == 1)
		{
			printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
			return (printf("Philo is alone and will dye\n"), 1);
		}
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	philo->last_meal_time = time_in_ms();
	printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
	printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);

	philo->meals_ate++;
	printf("Philosopher %i eats %i meals\n", philo->id, philo->meals_ate);

	if (philo->meals_ate == data->num_of_eats)
	{
		data->everyone_ate++;
		if (data->everyone_ate == data->philo_num)
		{
			usleep(data->time_to_eat * 1000);
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
			return (1);
		}
	}
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}

void	*make_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;
	int		y;

	y = 0;
	i = 0;
	philo = (t_philo *) arg;
	data = philo->data;
	while (data->stop && i < 1000000 && philo->id % 2 == 0)
	{
		i++;
	}
	while (data->stop && i < 1000000)
	{
		y++;
	}
	while (!data->stop)
	{
		if (eating_action(data, philo))
		{
			data->stop = 1;
		}
		
		printf("%lld %i is sleeping\n", time_in_ms() - data->start_time, philo->id);
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	philo_threads(t_data *data)
{
	int	i;

	i = 0;
	data->stop = 2;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_create(&data->philos[i].thread, NULL, make_routine, &data->philos[i]);
		i++;
	}
	data->stop = 0;
	data->start_time = time_in_ms();
	pthread_create(&data->monitor, NULL, monitor_actions, data->philos);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}
