/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:58:50 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/19 16:07:02 by fgata-va         ###   ########.fr       */
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

	void	catch_forks(t_philosopher *philo)
	{
		catch_a_fork(philo->left_fork, &philo->left_hand);
		if (philo->left_hand)
		{
			print_state(philo->philosopher_number, time_diff(&philo->last_meal),
				4, &philo->info->print_status);
			catch_a_fork(philo->right_fork, &philo->right_hand);
			if (philo->right_hand)
			{
				print_state(philo->philosopher_number, time_diff(&philo->last_meal),
					4, &philo->info->print_status);
			}
			else
			{
				usleep((philo->info->time_to_die - time_diff(&philo->last_meal))/4);
				catch_a_fork(philo->right_fork, &philo->right_hand);
				if (philo->right_hand)
					print_state(philo->philosopher_number, time_diff(&philo->last_meal),
						4, &philo->info->print_status);
					
				else
					drop_fork(philo->left_fork, &philo->left_hand);
			}
		}
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
				if (philo->left_hand && philo->right_hand)
				{
					eat(philo);
					drop_fork(philo->left_fork, &philo->left_hand);
					drop_fork(philo->right_fork, &philo->right_hand);
				}
			}
			else if (philo->state == sleepy)
				go_to_sleep(philo);
			if (philo->state != dead
				&& time_diff(&philo->last_meal) >= philo->info->time_to_die)
				philo->state = dead;
		}
	print_state(philo->philosopher_number, time_diff(&philo->last_meal),
		philo->state, &philo->info->print_status);
	return (NULL);
}
