/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:05:01 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/26 22:11:56 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	philo_saturated(t_philo *philo)
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

static void	philo_tasks(t_philo *philo)
{
	unsigned int	tmp;

	tmp = 0;
	while (!philo_saturated(philo) && !tmp)
	{
		pthread_mutex_lock(&philo->fork);
		print(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		print(FORK, philo);
		print(EAT, philo);
		pthread_mutex_lock(&philo->lock_count_eat);
		philo->count_eat++;
		pthread_mutex_unlock(&philo->lock_count_eat);
		pthread_mutex_lock(&philo->lock_last_eat);
		philo->t_last_eat = get_time();
		pthread_mutex_unlock(&philo->lock_last_eat);
		msleep(philo->data->t_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->l_fork);
		print(SLEEP, philo);
		msleep(philo->data->t_to_sleep);
		print(THINK, philo);
		pthread_mutex_lock(&philo->data->lock_dead);
		tmp = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock_dead);
	}
}

void	*philo_loop(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		print(THINK, philo);
		msleep(5);
	}
	philo_tasks(philo);
	return (NULL);
}

void	*survival_loop(void *arg)
{
	t_philo			*philo;
	unsigned int	i;
	unsigned int	tmp;

	philo = arg;
	i = 0;
	tmp = 0;
	while (!tmp)
	{
		pthread_mutex_lock(&philo->lock_last_eat);
		if ((get_time() - philo[i].t_last_eat) > philo->data->t_to_die)
		{
			print(DEATH, philo);
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
		}
		pthread_mutex_unlock(&philo->lock_last_eat);
		if (++i == philo->data->nbr_philos - 1)
			i = 0;
		pthread_mutex_lock(&philo->data->lock_dead);
		tmp = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock_dead);
	}
	return (NULL);
}
