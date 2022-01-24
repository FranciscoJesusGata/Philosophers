/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:48:11 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/24 15:52:47 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	massacre(t_philosopher *philosophers, int philo_num)
{
	int	i;

	i = 0;
	while (i != philo_num)
	{
		philosophers[i].state = dead;
		i++;
	}
}

void	dinner_vigilance(t_philosopher *philosophers, int philo_num, int meals)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (philosophers[i].state != dead)
	{
		if (i < philo_num && philosophers[i].meals == meals)
			finished++;
		if (finished == philo_num)
			break ;
		if (i == philo_num - 1)
		{
			i = 0;
			finished = 0;
		}
		else
			i++;
	}
	usleep(1000);
}

void	wait_philosophers(t_philosopher *philosophers, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void	waiter_loop(t_philosopher *philosophers, int philo_num, t_info *info)
{
	dinner_vigilance(philosophers, philo_num, info->times_must_eat);
	massacre(philosophers, philo_num);
	info->crash_the_party = true;
	pthread_mutex_unlock(&info->print_status);
	wait_philosophers(philosophers, info->number_of_philosophers);
}
