/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:21:22 by jakand            #+#    #+#             */
/*   Updated: 2025/09/04 20:56:30 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

long long	ft_atoi(const char *nptr)
{
	long long	i;
	long long	store;
	long long	sign;

	i = 0;
	store = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while ((unsigned char)nptr[i] >= '0' && (unsigned char)nptr[i] <= '9')
	{
		store = store * 10 + ((unsigned char)nptr[i] - 48);
		i++;
	}
	return (store * sign);
}
