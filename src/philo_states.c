/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:31:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/24 15:56:23 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_or_die(int wait, t_philosopher *philo)
{
	struct timeval	start;
	long			diff;
	long			last_meal;
	long			time_to_die;

	time_to_die = philo->info->time_to_die;
	last_meal = time_diff(&philo->last_meal);
	gettimeofday(&start, NULL);
	diff = 0;
	while (last_meal + diff < time_to_die && diff < wait)
	{
		usleep(10);
		diff = time_diff(&start);
	}
	if (last_meal + diff >= time_to_die)
		philo->state = dead;
	else if (philo->state == hungry)
		philo->state = sleepy;
	else if (philo->state == sleepy)
		philo->state = thoughtful;
}

void	go_to_sleep(t_philosopher *philo, struct timeval *start)
{
	print_state(philo, time_diff(start),
		&philo->info->print_status, &philo->info->crash_the_party);
	if (philo->state != dead)
		sleep_or_die(philo->info->time_to_sleep, philo);
}

void	eat(t_philosopher *philo, struct timeval *start)
{
	print_state(philo, time_diff(start),
		&philo->info->print_status, &philo->info->crash_the_party);
	if (philo->state != dead)
	{
		gettimeofday(&philo->last_meal, NULL);
		sleep_or_die(philo->info->time_to_eat, philo);
		philo->meals++;
	}
}

void	think(t_philosopher *philo, struct timeval *start)
{
	print_state(philo, time_diff(start),
		&philo->info->print_status, &philo->info->crash_the_party);
	if (philo->state != dead)
		philo->state = hungry;
}
