/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:40:57 by jakand            #+#    #+#             */
/*   Updated: 2025/08/29 17:02:05 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	init_data(t_data *data, int arc, char *arv[])
{
	int	i;

	//data->start_time = time_in_ms();
	data->philo_num = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arv[5])
		data->num_of_eats = ft_atoi(arv[5]);
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
		return (1);
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		printf("Philosopher %i\n", data->philos[i].id);
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_num;
		data->philos[i].data = data;
		i++;
	}
	if (philo_threads(data))
	{
		printf("Something happen\n");
		return (1);
	}
	printf("arc = %i\n", arc);
	printf("%i\n%i\n%i\n%i\n%i\n", data->philo_num, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->num_of_eats);
	return (0);
}
