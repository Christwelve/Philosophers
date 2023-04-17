/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/17 17:59:46 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define RED "\033[0;31m"
# define CLEAR "\033[0m"

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	count_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;

}	t_philo;

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	nbr_must_eat;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	pthread_mutex_t	eating;
	t_philo			*philo;

}	t_data;

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │ Utils                                                                   │
  └─────────────────────────────────────────────────────────────────────────┘
 */

int		is_num(char *argv);
int		int_max(char *argv);
long	ft_atol(const char *str);

#endif