/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:52 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/19 17:44:27 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	args_are_nbr(char **argv, int argc)
{
	int i;

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

int	parse_input(t_info *general_info, int argc, char **argv)
{
	if (!args_are_nbr(argv + 1, argc))
		print_error("all arguments has to be int natural numbers\n");
	else if (argc < 5 || argc > 6)
		print_error("not enought arguments\n\
Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	else
	{
		general_info->number_of_philosophers = ft_atoi(argv[1]);
		general_info->time_to_die = ft_atoi(argv[2]);
		general_info->time_to_eat = ft_atoi(argv[3]);
		general_info->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			general_info->times_must_eat = ft_atoi(argv[5]);
		else
			general_info->times_must_eat = -1;
		return (1);
	}
	return (0);
}

void	main_loop(t_philosopher *philosophers, int philo_num, t_info *info)
{
	int	i;

	i = 0;
	while (philosophers[i].state != dead)
	{
		if (i == philo_num - 1)
			i = 0;
		else
			i++;
	}
	i = 0;
	while (philosophers[i].state != dead)
	{
		pthread_detach(philosophers[i].thread);
		i++;
	}
	pthread_mutex_destroy(&info->print_status);
}

int	main(int argc, char *argv[])
{
	t_info			general_info;
	t_philosopher	*philosophers;
	t_fork			*forks;

	if (!(parse_input(&general_info, argc, argv)))
		return (1);
	forks = place_forks(general_info.number_of_philosophers);
	if (!forks)
		return (1);
	philosophers = sit_guests(forks, &general_info);
	if (!philosophers)
	{
		dismiss_guests(philosophers, forks,
			general_info.number_of_philosophers);
		return (1);
	}
	start_dinner(philosophers, general_info.number_of_philosophers);
	main_loop(philosophers, general_info.number_of_philosophers, &general_info);
	return (0);
}
