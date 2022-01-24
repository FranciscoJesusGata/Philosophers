/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:31:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/24 11:24:10 by fgata-va         ###   ########.fr       */
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

void	print_state(t_philosopher *philo, long time, pthread_mutex_t *lock, bool *crash_the_party)
{
	pthread_mutex_lock(lock);
	//printf("%d %s\n", guest + 1, info->crash_the_party ? "True" : "False");
	if (!*crash_the_party)
	{
		if (philo->state == hungry)
			printf("[%ld]%d is eating 🍝\n", time, philo->philosopher_number + 1);
		else if (philo->state == sleepy)
			printf("[%ld]%d is sleeping 💤\n", time, philo->philosopher_number + 1);
		else if (philo->state == thoughtful)
			printf("[%ld]%d is thinking 💭\n", time, philo->philosopher_number + 1);
		else if (philo->state == dead)
			printf("[%ld]%d died 💀\n", time, philo->philosopher_number + 1);
		if (philo->state != dead)
			pthread_mutex_unlock(lock);
	}
	else
		pthread_mutex_unlock(lock);
}

void	fork_print(int guest, long timestamp, pthread_mutex_t *lock, bool *crash_the_party)
{
	pthread_mutex_lock(lock);
	*crash_the_party = *crash_the_party;
	if (!*crash_the_party)
		printf("[%ld]%d has taken a fork 🍴\n", timestamp, guest + 1);
	pthread_mutex_unlock(lock);
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
