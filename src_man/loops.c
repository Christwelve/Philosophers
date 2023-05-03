/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:05:01 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/03 17:06:00 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	loop_1(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print(FORK, philo);
	last_eat_loop(philo);
	msleep(philo->data->t_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
}

static void	loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		msleep(philo->data->t_to_eat, philo);
	while (!philo_saturated(philo) && !check_dead(philo))
	{
		eat_loop(philo);
		print(SLEEP, philo);
		msleep(philo->data->t_to_sleep, philo);
		msleep(1, philo);
		print(THINK, philo);
		msleep(1, philo);
	}
}

void	*philo_loop(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->data->nbr_philos == 1)
		loop_1(philo);
	else if (philo->id % 2 == 0)
	{
		msleep(1, philo);
		loop(philo);
	}
	else if (philo->id % 3 == 0)
	{
		msleep(4, philo);
		loop(philo);
	}
	else
	{
		msleep(1, philo);
		loop(philo);
	}
	return (NULL);
}

void	*survival_loop(void *arg)
{
	t_philo			*philo;
	unsigned int	i;

	philo = arg;
	i = 0;
	while (!check_dead(philo) && !all_philos_saturated(philo))
	{
		pthread_mutex_lock(&philo->data->lock_time);
		pthread_mutex_lock(&philo->lock_last_eat);
		pthread_mutex_lock(&philo->lock_is_eating);
		if (((get_time() - philo[i].t_last_eat) > philo->data->t_to_die)
			&& !philo[i].is_eating)
		{
			print(DEATH, &philo[i]);
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
		}
		pthread_mutex_unlock(&philo->lock_is_eating);
		pthread_mutex_unlock(&philo->lock_last_eat);
		pthread_mutex_unlock(&philo->data->lock_time);
		if (++i >= philo->data->nbr_philos - 1)
			i = 0;
	}
	return (NULL);
}
