/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:52 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/15 11:08:09 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*place_forks(int number_of_philosophers)
{
	int i;
	t_fork *forks;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * number_of_philosophers);
	if (!forks)
		return (NULL);
	while (i < number_of_philosophers)
	{
		forks[i].available = 1;
		pthread_mutex_init(&forks[i].lock, NULL);
	}
	return (forks);
}

t_philosopher	*sit_guests(t_philosopher *philosophers, t_fork *forks,
		t_info *info)
{
	int i;

	i = 0;
	philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
		* info->number_of_philosophers);
	if (!philosophers)
		return (NULL);
	while (i < info->number_of_philosophers)
	{
		philosophers[i].philosopher_number = i;
		philosophers[i].is_alive = 1;
		philosophers[i].left_fork = 0;
		philosophers[i].right_fork = 0;
	}
	return (philosophers);
}

int	parse_input(t_info *general_info, int argc, char **argv)
{
	if (argc < 4 && argc > 6)
	{
		printf("Error: not enought arguments\n\
Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return(0);
	}
	general_info->number_of_philosophers = ft_atoi(argv[1]);
	general_info->time_to_die = ft_atoi(argv[2]);
	general_info->time_to_eat = ft_atoi(argv[3]);
	general_info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		general_info->times_must_eat = ft_atoi(argv[5]);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info general_info;
	t_philosopher *philosophers;
	t_fork *forks;

	if ((parse_input(&general_info, argc, argv)))
	{
		return (0);
	}
	return (1);
}
