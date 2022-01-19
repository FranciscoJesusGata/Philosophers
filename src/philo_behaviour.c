/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:58:50 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/19 19:09:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	void	catch_a_fork(t_fork *fork, bool *hand)
	{
		pthread_mutex_lock(&fork->lock);
		if (fork->available)
		{
			*hand = true;
			fork->available = false;
		}
		pthread_mutex_unlock(&fork->lock);
	}

	void	drop_fork(t_fork *fork, bool *hand)
	{
		pthread_mutex_lock(&fork->lock);
		*hand = false;
		fork->available = true;
		pthread_mutex_unlock(&fork->lock);
	}

	void	catch_forks(t_philosopher *philo, struct timeval *start)
	{
		if (philo->left_fork == philo->right_fork)
			return ;
		pthread_mutex_lock(&philo->left_fork->lock);
		pthread_mutex_lock(&philo->right_fork->lock);
		if (philo->left_fork->available && philo->right_fork->available)
		{
			philo->left_hand = true;
			philo->left_fork->available = false;
			print_state(philo->philosopher_number, time_diff(start),
					4, &philo->info->print_status);
			philo->right_hand = true;
			philo->right_fork->available = false;
			print_state(philo->philosopher_number, time_diff(start),
					4, &philo->info->print_status);
		}
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
	}

	void	*philo_behaviour(void *input)
	{
		t_philosopher	*philo;
		struct timeval	start;

		philo = (t_philosopher *)input;
		gettimeofday(&philo->last_meal, NULL);
		gettimeofday(&start, NULL);
		while (philo->state != dead)
		{
			if (philo->state == hungry)
			{
				catch_forks(philo, &start);
				if (philo->left_hand && philo->right_hand)
				{
					eat(philo, &start);
					drop_fork(philo->left_fork, &philo->left_hand);
					drop_fork(philo->right_fork, &philo->right_hand);
				}
				else
					usleep((philo->info->time_to_die - time_diff(&philo->last_meal))/10);
			}
			else if (philo->state == sleepy)
				go_to_sleep(philo, &start);
			else if (philo->state == thoughtful)
			{
				print_state(philo->philosopher_number, time_diff(&start),
					philo->state, &philo->info->print_status);
				philo->state = hungry;
			}
			if (philo->state != dead
				&& time_diff(&philo->last_meal) >= philo->info->time_to_die)
				philo->state = dead;
		}
	print_state(philo->philosopher_number, time_diff(&start),
		philo->state, &philo->info->print_status);
	return (NULL);
}
