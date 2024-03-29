/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:57:45 by fgata-va          #+#    #+#             */
/*   Updated: 2022/01/26 16:24:51 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "philo_structs.h"

void			*philo_behaviour(void *input);
void			waiter_loop(t_philosopher *philos, int philo_num,
					t_info *info);
void			start_dinner(t_philosopher *philosophers, int philo_num,
					struct timeval *start);
void			eat(t_philosopher *philo);
void			go_to_sleep(t_philosopher *philo);
void			print_state(t_philosopher *philo, pthread_mutex_t *lock,
					bool *crash_the_party);
void			fork_print(int guest, long timestamp,
					pthread_mutex_t *lock, bool *crash_the_party);

/*
** Utils Functions
*/
int				ft_atoi(const char *str);
bool			ft_isnumer(const char *str);
void			print_error(char *msg);
long			time_diff(struct timeval *time);

/*
** Memory management
*/
t_fork			*place_forks(int number_of_philosophers);
t_philosopher	*sit_guests(t_fork *forks, t_info *info,
					struct timeval *start);
void			dismiss_guests(t_philosopher *philosophers, t_fork *forks,
					int number_of_philosophers, t_info *info);

#endif
