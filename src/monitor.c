/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:27:37 by jaandras          #+#    #+#             */
/*   Updated: 2025/09/04 20:36:08 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo, int i)
{
	if (time_in_ms() - philo[i].last_meal_time > philo->data->time_to_die)
	{
		printf("%lld %d died\n", time_in_ms() - philo->data->start_time,
			philo[i].id);
		philo->data->stop = 1;
		return (1);
	}
	return (0);
}

int	check_meals_ate(t_philo *philo)
{
	if (philo->meals_ate == philo->data->num_of_eats)
	{
		philo->data->everyone_ate++;
		if (philo->data->everyone_ate == philo->data->philo_num)
		{
			philo->data->stop = 1;
			return (1);
		}
	}
	return (0);
}

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
			if (check_death(philo, i))
				return (NULL);
			if (check_meals_ate(philo))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
