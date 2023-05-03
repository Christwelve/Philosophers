/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/03 13:31:22 by cmeng            ###   ########.fr       */
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
	unsigned int	is_eating;
	pthread_mutex_t	lock_is_eating;
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
	pthread_mutex_t	lock_time;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_print;
	pthread_t		death_thread;
	t_philo			*philo;

}	t_data;

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │Parser		                                                            │
  └─────────────────────────────────────────────────────────────────────────┘
 */

int				check_input(int argc, char **argv);
long			ft_atol(const char *str);

int				set_data(int argc, char **argv, t_data *data);
int				set_philo(t_data *data);

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │Functions	                                                            │
  └─────────────────────────────────────────────────────────────────────────┘
 */

int				create_threads(t_data *data);
int				join_threads(t_data *data);

void			*philo_loop(void *arg);
void			*survival_loop(void *arg);

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │Utils		                                                            │
  └─────────────────────────────────────────────────────────────────────────┘
 */

unsigned int	check_dead(t_philo *philo);
int				philo_saturated(t_philo *philo);
int				all_philos_saturated(t_philo *philo);
void			last_eat_loop(t_philo *philo);
void			eat_loop(t_philo *philo);

unsigned long	get_time(void);
void			msleep(int ms, t_philo *philo);
void			free_data(t_data *data);
void			free_all(t_data *data);
void			print(int in, t_philo *philo);

#endif