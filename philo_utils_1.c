/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:58:20 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/13 19:16:15 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	resp;
	int		i;
	int		n;

	i = 0;
	resp = 0;
	n = 1;
	while ((str[i] >= 11 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		resp = (resp * 10) + (str[i] - '0');
		if (resp > 2147483647 && n == 1)
			return (-1);
		else if (resp > 2147483648 && n == -1)
			return (0);
		i++;
	}
	return ((int)(resp * n));
}
