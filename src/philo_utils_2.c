/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:37:44 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/17 12:48:45 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

float		time_diff(struct timeval *time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec * 1e6 + current_time.tv_usec)
			- (time->tv_sec * 1e6 + time->tv_sec)) / 1e3);
}
