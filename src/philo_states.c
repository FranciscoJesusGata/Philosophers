/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:31:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/17 14:50:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_or_die(int wait, int tol, int ttd, t_state *state)
{
	struct timeval	time;
	float			diff;

	gettimeofday(&time, NULL);
	diff = 0;
	while (tol + diff < ttd && diff < wait)
	{
		sleep(1);
		diff = time_diff(&time);
	}
	if (tol + diff >= ttd)
		*state = dead;
	else if (*state == hungry)
		*state = sleepy;
	else
		*state = thoughtful;
}

void	print_state(int guest, int time, t_state state, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("[%d]%d ", time, guest);
	if (state == hungry)
		printf("is eating 🍝");
	else if (state == sleepy)
		printf("is sleeping 💤");
	else if (state == thoughtful)
		printf("is thinking 💭");
	else if (state == dead)
	{
		printf("is dead 💀");
		return ;
	}
	else
		printf("has taken a fork 🍴");
	pthread_mutex_unlock(lock);
}

void	go_to_sleep(t_philosopher *philo)
{
	print_state(philo->philosopher_number, time_diff(&philo->last_meal),
		philo->state, philo->info->print_status);
	sleep_or_die(philo->info->time_to_sleep, time_diff(&philo->last_meal),
		philo->info->time_to_die, &philo->state);
	if (philo->state != dead)
		philo->state = hungry;
}

void	eat(t_philosopher *philo)
{
	print_state(philo->philosopher_number, time_diff(&philo->last_meal),
		philo->state, philo->info->print_status);
	gettimeofday(&philo->last_meal, NULL);
	sleep_or_die(philo->info->time_to_eat, time_diff(&philo->last_meal),
		philo->info->time_to_die, &philo->state);
}

