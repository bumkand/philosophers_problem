/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:21:22 by jakand            #+#    #+#             */
/*   Updated: 2025/08/27 22:22:05 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	long int		store;
	int				sign;

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
