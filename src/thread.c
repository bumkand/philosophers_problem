/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:09:14 by jakand            #+#    #+#             */
/*   Updated: 2025/09/05 22:12:42 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*make_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&data->meal);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->meal);
			break ;
		}
		pthread_mutex_unlock(&data->meal);
		if (eating_action(data, philo))
			break ;
		usleep(500);
		if (sleep_and_think(data, philo))
			break ;
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
		pthread_create(&data->philos[i].thread, NULL, make_routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_actions, data->philos);
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	return (0);
}
