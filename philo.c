/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:52 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/13 13:56:16 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc < 4 && argc > 6)
	{
		printf("Error: not enought arguments\n\
Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return(1);
	}
	int i = 1;
	while (argv[i])
	{
		printf("argv[i]: \"%s\"\n", argv[i]);
		i++;
	}
}
