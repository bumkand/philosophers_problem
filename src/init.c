/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:40:57 by jakand            #+#    #+#             */
/*   Updated: 2025/09/06 17:22:14 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	data_struct(t_data *data, char *arv[])
{
	data->philo_num = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arv[5])
		data->num_of_eats = ft_atoi(arv[5]);
	else
		data->num_of_eats = -1;
	data->stop = 0;
	data->start_time = time_in_ms();
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
		return (1);
	return (0);
}

int	philo_struct(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_num;
		data->philos[i].data = data;
		data->philos[i].meals_ate = 0;
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	return (0);
}

int	init_data(t_data *data, char *arv[])
{
	if (data_struct(data, arv))
	{
		printf("Initialization in data struct went wrong\n");
		return (1);
	}
	if (data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	{
		printf("Wrong amount of time\n");
		return (1);
	}
	philo_struct(data);
	return (0);
}
