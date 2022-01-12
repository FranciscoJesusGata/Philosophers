/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:31:33 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/12 19:35:23 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int guest, int time, int state, pthread_mutex_t *lock)
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
	}
	else
		printf("has taken a fork 🍴");
	pthread_mutex_unlock(lock);
}

void	go_to_sleep(t_philosopher *philo)
{
	print_state(philo->philosopher_number, time_diff(philo->last_meal),
		philo->state, philo->info->print_status);
	philo->state = sleep_or_die(philo->info->time_to_sleep, philo->last_meal,
		philo->info->time_to_die);
}

void	eat(t_philosopher *philo)
{
	print_state(philo->philosopher_number, time_diff(philo->last_meal),
		philo->state, philo->info->print_status);
	gettimeofday(&philo->last_meal, NULL);
	philo->state = sleep_or_die(philo->info->time_to_eat, philo->last_meal,
		philo->info->time_to_die);
}

