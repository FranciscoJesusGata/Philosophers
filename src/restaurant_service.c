/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restaurant_service.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:04:31 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/08 19:18:19 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*place_forks(int number_of_philosophers)
{
	int i;
	t_fork *forks;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * number_of_philosophers);
	if (!forks)
		return (NULL);
	while (i < number_of_philosophers)
	{
		forks[i].available = 1;
		pthread_mutex_init(&forks[i].lock, NULL);
		i++;
	}
	return (forks);
}

t_philosopher	*sit_guests(t_fork *forks,
		t_info *info)
{
	int i;
	t_philosopher *philosophers;

	i = 0;
	philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
		* info->number_of_philosophers);
	if (!philosophers)
		return (NULL);
	while (i < info->number_of_philosophers)
	{
		philosophers[i].philosopher_number = i;
		philosophers[i].state = hungry;
		philosophers[i].left_hand = false;
		philosophers[i].right_hand = false;
		philosophers[i].left_fork = &forks[i];
		if (i == (info->number_of_philosophers - 1))
			philosophers[i].right_fork = &forks[0];
		else
			philosophers[i].right_fork = &forks[i + 1];
		i++;
	}
	return (philosophers);
}

void	dismiss_guests(t_philosopher *philosophers, t_fork *forks,
		int number_of_philosophers)
{
	int	i;

	if (philosophers)
		free(philosophers);
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	free(forks);
}

void	start_dinner(t_philosopher *philosophers, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthead_create(philosophers[i].thread, NULL, philo_behaviour,
			philosophers[i]);
		i++;
	}
}
