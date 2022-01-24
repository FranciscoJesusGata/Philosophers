/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:56:11 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/24 15:58:12 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philosopher *philo, long time, pthread_mutex_t *lock,
	bool *crash_the_party)
{
	pthread_mutex_lock(lock);
	if (!*crash_the_party)
	{
		if (philo->state == hungry)
			printf("[%ld]%d is eating 🍝\n", time,
				philo->philosopher_number + 1);
		else if (philo->state == sleepy)
			printf("[%ld]%d is sleeping 💤\n", time,
				philo->philosopher_number + 1);
		else if (philo->state == thoughtful)
			printf("[%ld]%d is thinking 💭\n", time,
				philo->philosopher_number + 1);
		else if (philo->state == dead)
			printf("[%ld]%d died 💀\n", time,
				philo->philosopher_number + 1);
		if (philo->state != dead)
			pthread_mutex_unlock(lock);
	}
	else
		pthread_mutex_unlock(lock);
}

void	fork_print(int guest, long timestamp, pthread_mutex_t *lock,
	bool *crash_the_party)
{
	pthread_mutex_lock(lock);
	*crash_the_party = *crash_the_party;
	if (!*crash_the_party)
		printf("[%ld]%d has taken a fork 🍴\n", timestamp, guest + 1);
	pthread_mutex_unlock(lock);
}
