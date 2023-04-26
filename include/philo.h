/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/26 22:17:42 by cmeng            ###   ########.fr       */
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

# define FORK	0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define DEATH	4
# define EATEN	5

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	count_eat;
	unsigned long	t_last_eat;
	pthread_mutex_t	lock_count_eat;
	pthread_mutex_t	lock_last_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	*l_fork;

	t_data			*data;

}	t_philo;

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	nbr_must_eat;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	unsigned long	t_start;
	unsigned int	dead;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_print;
	pthread_t		death_thread;
	t_philo			*philo;

}	t_data;

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │ Utils                                                                   │
  └─────────────────────────────────────────────────────────────────────────┘
 */

int				check_input(int argc, char **argv);
long			ft_atol(const char *str);

unsigned long	get_time(void);
void			msleep(int ms);
void			free_all(t_data *data);
void			print(int in, t_philo *philo);

void			*philo_loop(void *arg);
void			*survival_loop(void *arg);

int				create_threads(t_data *data);
int				join_threads(t_data *data);

int				set_philo(t_data *data);
int				set_data(int argc, char **argv, t_data *data);

#endif