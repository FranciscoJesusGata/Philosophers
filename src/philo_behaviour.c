/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:58:50 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/23 21:21:14 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_fork(t_fork *fork, bool *hand)
{
	pthread_mutex_lock(&fork->lock);
	*hand = false;
	fork->available = true;
	pthread_mutex_unlock(&fork->lock);
}

void	leave_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->lock);
	pthread_mutex_lock(&philo->right_fork->lock);
	philo->left_hand = false;
	philo->left_fork->available = true;
	philo->right_hand = false;
	philo->right_fork->available = true;
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
}

void	catch_a_fork(t_philosopher *philo, t_fork *fork, bool *hand, long time)
{
	pthread_mutex_lock(&fork->lock);
	if (fork->available)
	{
		*hand = true;
		fork->available = false;
		fork_print(philo->philosopher_number, time,
			&philo->info->print_status, &philo->info->crash_the_party);
	}
	pthread_mutex_unlock(&fork->lock);
}

void	take_forks(t_philosopher *philo, struct timeval *start)
{
	if ((philo->philosopher_number + 1) != philo->info->number_of_philosophers)
	{
		if (!philo->left_hand)
			catch_a_fork(philo, philo->left_fork, &philo->left_hand, time_diff(start));
		else
			catch_a_fork(philo, philo->right_fork, &philo->right_hand, time_diff(start));
	}
	else
	{
		if (!philo->right_hand)
			catch_a_fork(philo, philo->right_fork, &philo->right_hand, time_diff(start));
		else
			catch_a_fork(philo, philo->left_fork, &philo->left_hand, time_diff(start));
	}
	/*if (!philo->left_hand)
		catch_a_fork(philo->left_fork, &philo->left_hand);
	if (!philo->right_hand)
		catch_a_fork(philo->left_fork, &philo->right_hand);*/
	if (philo->left_hand && philo->right_hand)
	{
		eat(philo, start);
		leave_forks(philo);
	}
}

void	*philo_behaviour(void *input)
{
	t_philosopher	*philo;
	struct timeval	start;

	philo = (t_philosopher *)input;
	gettimeofday(&start, NULL);
	if ((philo->philosopher_number + 1) % 2 != 0)
		usleep(1e3);
	gettimeofday(&philo->last_meal, NULL);
	while (philo->state != dead
		&& philo->meals != philo->info->times_must_eat)
	{
		if (time_diff(&philo->last_meal) >= philo->info->time_to_die)
			philo->state = dead;
		else if (philo->state == hungry)
			take_forks(philo, &start);
		else if (philo->state == sleepy)
			go_to_sleep(philo, &start);
		else if (philo->state == thoughtful)
			think(philo, &start);
	}
	leave_forks(philo);
	if (philo->state == dead)
		print_state(philo->philosopher_number, time_diff(&start),
		dead, philo->info);
	return (NULL);
}
