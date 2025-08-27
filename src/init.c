/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:40:57 by jakand            #+#    #+#             */
/*   Updated: 2025/08/27 22:42:09 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*init_data(t_data *data, int arc, char *arv[])
{
	int	i;

	data->philo_num = ft_atoi(arv[1]);
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
		return (1);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_num;
		i++;
	}
}