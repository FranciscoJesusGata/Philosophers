/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:24:14 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/08 19:17:01 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include "philo.h"

typedef enum e_states {
	dead,
	hungry,
	thoughtful,
	sleepy
}			t_state;

typedef struct s_info
{
	pthread_mutex_t	*print_status;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				crash_the_party;
}					t_info;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philosopher
{
	int				philosopher_number;
	pthread_t		thread;
	t_state			state;
	struct timeval	last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	bool			left_hand;
	bool			right_hand;
}					t_philosopher;

#endif
