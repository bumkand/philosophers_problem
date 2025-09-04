/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:09:14 by jakand            #+#    #+#             */
/*   Updated: 2025/09/04 17:06:46 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_actions(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		i = 0;
		while (i < philo->data->philo_num)
		{
			if (time_in_ms() - philo[i].last_meal_time > philo->data->time_to_die)
			{
				printf("%lld %d died\n\n\n\n", time_in_ms()
					- philo->data->start_time, philo[i].id);
				philo->data->stop = 1;
				return (NULL);
			}
			if (philo->meals_ate == philo->data->num_of_eats)
		{
			philo->data->everyone_ate++;
			if (philo->data->everyone_ate == philo->data->philo_num)
			{
				philo->data->stop = 1;
				usleep(philo->data->time_to_eat * 1000);
				return (NULL);
			}
		}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	eating_action(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		philo->last_meal_time = time_in_ms();
		pthread_mutex_lock(&data->print);
		if (philo->data->stop)
			return (pthread_mutex_unlock(&data->print), 1);
		printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
		printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);
		philo->meals_ate++;
		pthread_mutex_unlock(&data->print);
		printf("Philosopher %i eats %i meals\n", philo->id, philo->meals_ate);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		philo->last_meal_time = time_in_ms();
		pthread_mutex_lock(&data->print);
		if (philo->data->stop)
			return (pthread_mutex_unlock(&data->print), 1);
		printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time, philo->id);
		printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);
		philo->meals_ate++;
		pthread_mutex_unlock(&data->print);
		printf("Philosopher %i eats %i meals\n", philo->id, philo->meals_ate);
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

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 1)
		usleep(500);
	while (!data->stop)
	{
		if (eating_action(data, philo))
		{
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
			data->stop = 1;
		}
		
		pthread_mutex_lock(&data->print);
		if (data->stop)
			return (pthread_mutex_unlock(&data->print), NULL);
		printf("%lld %i is sleeping\n", time_in_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		usleep(data->time_to_sleep * 1000);
		
		pthread_mutex_lock(&data->print);
		if (data->stop)
			return (pthread_mutex_unlock(&data->print), NULL);
		printf("%lld %i is thinking\n", time_in_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		usleep(500);
	}
	return (NULL);
}

int	philo_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = time_in_ms();
	pthread_mutex_init(&data->print, NULL);
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_create(&data->philos[i].thread, NULL, make_routine, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_actions, data->philos);
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	i = -1;
	pthread_mutex_destroy(&data->print);
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	return (0);
}
