/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:27:37 by jaandras          #+#    #+#             */
/*   Updated: 2025/09/05 22:08:19 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->meal);
	if (time_in_ms() - philo[i].last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d died\n", time_in_ms() - philo->data->start_time,
			philo[i].id);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal);
	return (0);
}

int	check_meals_ate(t_philo *philo)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	if (philo->data->num_of_eats == -1)
		return (0);
	pthread_mutex_lock(&philo->data->meal);
	while (i < philo->data->philo_num)
	{
		if (philo[i].meals_ate >= philo->data->num_of_eats)
			finished_count++;
		i++;
	}
	if (finished_count == philo->data->philo_num)
	{
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal);
	return (0);
}

void	*monitor_actions(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->meal);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->meal);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meal);
		i = 0;
		while (i < philo->data->philo_num)
		{
			if (check_death(philo, i))
				return (NULL);
			i++;
		}
		if (check_meals_ate(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
