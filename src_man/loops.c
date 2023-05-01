/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:05:01 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/01 19:55:40 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_loop(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		msleep(philo->data->t_to_sleep, philo);
		while (!philo_saturated(philo) && !check_dead(philo))
		{
			eat_loop(philo, 0);
			print(SLEEP, philo);
			msleep(philo->data->t_to_sleep, philo);
			print(THINK, philo);
		}
	}
	else
	{
		while (!philo_saturated(philo) && !check_dead(philo))
		{
			eat_loop(philo, 1);
			print(SLEEP, philo);
			msleep(philo->data->t_to_sleep, philo);
			print(THINK, philo);
		}
	}
	return (NULL);
}

static int	all_philos_saturated(t_philo *philo)
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
		if ((get_time() - philo[i].t_last_eat) > philo->data->t_to_die)
		{
			print(DEATH, &philo[i]);
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
		}
		pthread_mutex_unlock(&philo->lock_last_eat);
		pthread_mutex_unlock(&philo->data->lock_time);
		if (++i == philo->data->nbr_philos - 1)
			i = 0;
	}
	return (NULL);
}
