/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:30:34 by jakand            #+#    #+#             */
/*   Updated: 2025/09/02 16:01:47 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int arc, char *arv[])
{
	t_data	data;
	//int		i;

	//i = 0;
	if (arc < 5 || arc > 6)
		return (printf("Wrong amount of arguments\n"), 0);

	if (init_data(&data, arc, arv))
	{
		if (data.forks)
			free(data.forks);
		if (data.philos)
			free(data.philos);
		return (1);
	}
	//printf("main ==> %lli %lli %lli %lli\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep);
	if (philo_threads(&data))
	{
		if (data.forks)
			free(data.forks);
		if (data.philos)
			free(data.philos);
		printf("Something happen\n");
		return (1);
	}
	if (data.forks)
		free(data.forks);
	if (data.philos)
		free(data.philos);

	return (0);
}
