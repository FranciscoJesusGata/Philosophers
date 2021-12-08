/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:57:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/08 16:33:25 by fgata-va         ###   ########.fr       */
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

/*
** Utils Functions
*/

int				ft_atoi(const char *str);
bool			ft_isnumer(const char *str);
void			print_error(char *msg);

/*
** Memory management
*/
t_fork			*place_forks(int number_of_philosophers);
t_philosopher	*sit_guests(t_fork *forks, t_info *info);
void			dismiss_guests(t_philosopher *philosophers, t_fork *forks,
					int number_of_philosophers);

#endif
