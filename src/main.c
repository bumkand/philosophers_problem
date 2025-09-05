/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:30:34 by jakand            #+#    #+#             */
/*   Updated: 2025/09/05 17:44:25 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_arv(char *arv[])
{
	int		i;
	int		j;
	long	k;

	i = 1;
	if (arv[5])
	{
		k = ft_atoi(arv[5]);
		if (k < 1)
			return (1);
	}
	k = ft_atoi(arv[1]);
	if (k < 1)
		return (1);
	while (arv[i])
	{
		j = 0;
		if (arv[i][j] == '-')
			j++;
		while (arv[i][j])
		{
			while (arv[i][j] == ' ' || (arv[i][j] >= 9 && arv[i][j] <= 13))
				j++;
			if (arv[i][j] < '0' || arv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int arc, char *arv[])
{
	t_data	data;

	if (arc < 5 || arc > 6)
		return (printf("Wrong amount of arguments\n"), 0);
	if (check_arv(arv))
	{
		printf("Wrong argument type or num of meals or philos < 1\n");
		return (1);
	}
	if (init_data(&data, arv))
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
