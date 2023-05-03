/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:11:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/03 17:04:15 by cmeng            ###   ########.fr       */
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

// void	last_eat_loop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->lock_time);
// 	pthread_mutex_lock(&philo->lock_last_eat);
// 	philo->t_last_eat = get_time();
// 	pthread_mutex_unlock(&philo->lock_last_eat);
// 	pthread_mutex_unlock(&philo->data->lock_time);
// }

// static void	is_eating(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->lock_is_eating);
// 	philo->is_eating = 1;
// 	pthread_mutex_unlock(&philo->lock_is_eating);
// }

// static void	is_not_eating(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->lock_is_eating);
// 	philo->is_eating = 0;
// 	pthread_mutex_unlock(&philo->lock_is_eating);
// }

// static void	count_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->lock_count_eat);
// 	philo->count_eat++;
// 	pthread_mutex_unlock(&philo->lock_count_eat);
// }

// void	eat_loop(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->l_fork);
// 		print(FORK, philo);
// 		pthread_mutex_lock(&philo->fork);
// 		print(FORK, philo);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->fork);
// 		print(FORK, philo);
// 		pthread_mutex_lock(philo->l_fork);
// 		print(FORK, philo);
// 	}
// 	is_eating(philo);
// 	last_eat_loop(philo);
// 	print(EAT, philo);
// 	msleep(philo->data->t_to_eat, philo);
// 	count_eat(philo);
// 	msleep(1, philo);
// 	is_not_eating(philo);
// 	pthread_mutex_unlock(&philo->fork);
// 	pthread_mutex_unlock(philo->l_fork);
// }
