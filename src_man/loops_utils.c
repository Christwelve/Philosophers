/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:11:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/02 08:16:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	check_dead(t_philo *philo)
{
	unsigned int	tmp;

	tmp = 0;
	pthread_mutex_lock(&philo->data->lock_dead);
	tmp = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock_dead);
	return (tmp);
}

int	philo_saturated(t_philo *philo)
{
	unsigned int	i;

	pthread_mutex_lock(&philo->lock_count_eat);
	i = philo->count_eat;
	pthread_mutex_unlock(&philo->lock_count_eat);
	if (philo->data->nbr_must_eat != 0)
	{
		if (i < philo->data->nbr_must_eat)
			return (0);
		else
			return (1);
	}
	return (0);
}

int	all_philos_saturated(t_philo *philo)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < philo->data->nbr_philos)
	{
		if (philo_saturated(&philo[i]))
			res++;
		i++;
	}
	if (res == philo->data->nbr_philos)
		return (1);
	return (0);
}

void	last_eat_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_time);
	pthread_mutex_lock(&philo->lock_last_eat);
	philo->t_last_eat = get_time();
	pthread_mutex_unlock(&philo->lock_last_eat);
	pthread_mutex_unlock(&philo->data->lock_time);
}

void	eat_loop(t_philo *philo, int odd)
{
	if (odd)
	{
		pthread_mutex_lock(&philo->fork);
		print(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		print(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print(FORK, philo);
		pthread_mutex_lock(&philo->fork);
		print(FORK, philo);
	}
	print(EAT, philo);
	pthread_mutex_lock(&philo->lock_count_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->lock_count_eat);
	last_eat_loop(philo);
	msleep(philo->data->t_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->l_fork);
}
