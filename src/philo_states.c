/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:31:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/20 11:01:28 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_or_die(int wait, int tol, int ttd, t_state *state)
{
	struct timeval	time;
	int			diff;

	gettimeofday(&time, NULL);
	diff = 0;
	while (tol + diff < ttd && diff < wait)
	{
		usleep(1);
		diff = time_diff(&time);
	}
	if (tol + diff >= ttd)
		*state = dead;
	else if (*state == hungry)
		*state = sleepy;
	else
		*state = thoughtful;
}

void	print_state(int guest, int time, t_state state, t_info *info)
{
	pthread_mutex_lock(&info->print_status);
	if (info->crash_the_party)
	{
		pthread_mutex_unlock(&info->print_status);
		return ;
	}
	if (state == hungry)
		printf("[%d]%d is eating 🍝\n", time, guest + 1);
	else if (state == sleepy)
		printf("[%d]%d is sleeping 💤\n", time, guest + 1);
	else if (state == thoughtful)
		printf("[%d]%d is thinking 💭\n", time, guest + 1);
	else if (state == dead)
		printf("[%d]%d died 💀\n", time, guest + 1);
	else
		printf("[%d]%d has taken a fork 🍴\n", time, guest + 1);
	if (state != dead)
		pthread_mutex_unlock(&info->print_status);
}

void	go_to_sleep(t_philosopher *philo, struct timeval *start)
{
	print_state(philo->philosopher_number, time_diff(start),
		philo->state, philo->info);
	sleep_or_die(philo->info->time_to_sleep, time_diff(&philo->last_meal),
		philo->info->time_to_die, &philo->state);
}

void	eat(t_philosopher *philo, struct timeval *start)
{
	print_state(philo->philosopher_number, time_diff(start),
		philo->state, philo->info);
	gettimeofday(&philo->last_meal, NULL);
	sleep_or_die(philo->info->time_to_eat, time_diff(&philo->last_meal),
		philo->info->time_to_die, &philo->state);
	philo->meals++;
}

void	think(t_philosopher *philo, struct timeval *start)
{
	print_state(philo->philosopher_number, time_diff(start),
		philo->state, philo->info);
	philo->state = hungry;
}
