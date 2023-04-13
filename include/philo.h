/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:48:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/13 17:33:35 by cmeng            ###   ########.fr       */
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

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	nbr_must_eat;

}	t_data;

typedef struct s_philo
{
	unsigned int	id;
	t_data			*data;

}	t_philo;

/*
  ┌─────────────────────────────────────────────────────────────────────────┐
  │ Utils                                                                   │
  └─────────────────────────────────────────────────────────────────────────┘
 */

int		is_num(char *argv);
int		int_max(char *argv);

#endif