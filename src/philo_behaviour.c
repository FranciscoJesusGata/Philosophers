/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:47:01 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/12 19:31:52 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	catch_a_fork(t_fork *fork, bool hand)
{
	pthread_mutex_lock(&fork->lock);
	if (fork->available)
	{
		hand = true;
		fork->available = false;
	}
	pthread_mutex_unlock(&fork->lock);

}

void	drop_fork(t_fork *fork, bool hand)
{
	pthread_mutex_lock(&fork->lock);
	if (fork->available)
	{
		hand = false;
		fork->available = true;
	}
	pthread_mutex_unlock(&fork->lock);

}

void	catch_forks(t_philosopher *philo)
{
	catch_a_fork(philo->left_fork, philo->left_hand);
	if (philo->left_hand)
		catch_a_fork(philo->right_fork, philo->right_hand);
}

void	*philo_behaviour(void *input)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)input;
	gettimeofday(&philo->last_meal, NULL);
	while (philo->state != dead)
	{
		if (philo->state == hungry)
		{
			catch_forks(philo);
			if (philo->left_fork && philo->right_fork)
				eat(philo);
		}
		else if (philo->state == sleepy)
			go_to_sleep(philo);
		if (philo->state != dead
			&& time_diff(philo->last_meal) >= philo->info->time_to_die)
			philo->state = dead;
	}
	print_state(philo->philosopher_number, time_diff(philo->last_meal),
		philo->state);
	return (NULL);
}
