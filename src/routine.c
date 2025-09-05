/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:13:20 by jaandras          #+#    #+#             */
/*   Updated: 2025/09/05 22:12:46 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sleep_and_think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal);
	if (data->stop)
		return (pthread_mutex_unlock(&data->meal), 1);
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->print);
	printf("%lld %i is sleeping\n", time_in_ms() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	usleep(data->time_to_sleep * 1000);
	pthread_mutex_lock(&data->meal);
	if (data->stop)
		return (pthread_mutex_unlock(&data->meal), 1);
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->print);
	printf("%lld %i is thinking\n", time_in_ms() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	usleep(500);
	return (0);
}

int	even_philosophers(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	pthread_mutex_lock(&data->meal);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->meal);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->print);
	printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time,
		philo->id);
	printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->meal);
	philo->last_meal_time = time_in_ms();
	philo->meals_ate++;
	pthread_mutex_unlock(&data->meal);
	return (0);
}

int	odd_philosophers(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->meal);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->meal);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		return (1);
	}
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->print);
	printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time,
		philo->id);
	printf("%lld %i is eating\n", time_in_ms() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->meal);
	philo->last_meal_time = time_in_ms();
	philo->meals_ate++;
	pthread_mutex_unlock(&data->meal);
	return (0);
}

int	eating_action(t_data *data, t_philo *philo)
{
	if (data->philo_num == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		pthread_mutex_lock(&data->print);
		printf("%lld %i has taken a fork\n", time_in_ms() - data->start_time,
			philo->id);
		pthread_mutex_unlock(&data->print);
		pthread_mutex_lock(&data->meal);
		philo->last_meal_time = time_in_ms();
		pthread_mutex_unlock(&data->meal);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		if (even_philosophers(data, philo))
			return (1);
	}
	else
	{
		if (odd_philosophers(data, philo))
			return (1);
	}
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (0);
}
