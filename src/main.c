/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:30:34 by jakand            #+#    #+#             */
/*   Updated: 2025/08/31 22:11:45 by jakand           ###   ########.fr       */
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
		printf("Something went wrong\n");
		return (0);
	}

	if (data.forks)
		free(data.forks);
	if (data.philos)
		free(data.philos);

	return (0);
}
