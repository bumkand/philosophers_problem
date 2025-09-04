/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:30:34 by jakand            #+#    #+#             */
/*   Updated: 2025/09/04 20:44:02 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int arc, char *arv[])
{
	t_data	data;

	if (arc < 5 || arc > 6)
		return (printf("Wrong amount of arguments\n"), 0);
	if (init_data(&data, arc, arv))
	{
		free_data(&data);
		return (1);
	}
	if (philo_threads(&data))
	{
		free_data(&data);
		printf("Something happen\n");
		return (1);
	}
	free_data(&data);
	return (0);
}
