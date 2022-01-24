/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:52 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/24 15:52:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	args_are_nbr(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnumer(*argv))
			return (false);
		argv++;
		i++;
	}
	return (true);
}

int	parse_input(t_info *info, int argc, char **argv)
{
	if (!args_are_nbr(argv + 1, argc))
		print_error("all arguments has to be int natural numbers\n");
	else if (argc < 5 || argc > 6)
		print_error("not enought arguments\n\
Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	else
	{
		info->number_of_philosophers = ft_atoi(argv[1]);
		info->time_to_die = ft_atoi(argv[2]);
		info->time_to_eat = ft_atoi(argv[3]);
		info->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			info->times_must_eat = ft_atoi(argv[5]);
		else
			info->times_must_eat = -1;
		info->crash_the_party = false;
		pthread_mutex_init(&info->print_status, NULL);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info			info;
	t_philosopher	*philosophers;
	t_fork			*forks;

	if (!(parse_input(&info, argc, argv)))
		return (1);
	forks = place_forks(info.number_of_philosophers);
	if (!forks)
		return (1);
	philosophers = sit_guests(forks, &info);
	if (!philosophers)
	{
		dismiss_guests(philosophers, forks,
			info.number_of_philosophers, &info);
		return (1);
	}
	start_dinner(philosophers, info.number_of_philosophers);
	waiter_loop(philosophers, info.number_of_philosophers, &info);
	dismiss_guests(philosophers, forks, info.number_of_philosophers, &info);
}
