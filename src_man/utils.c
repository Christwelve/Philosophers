/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:45:19 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/27 06:12:39 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msleep(int ms)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < (unsigned long) ms)
		usleep(100);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->lock_dead);
	pthread_mutex_destroy(&data->lock_print);
}

void	free_all(t_data *data)
{
	pthread_mutex_destroy(&data->lock_dead);
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->philo->lock_count_eat);
	pthread_mutex_destroy(&data->philo->lock_last_eat);
	pthread_mutex_destroy(&data->philo->fork);
	pthread_mutex_destroy(data->philo->l_fork);
	free(data->philo);
}

void	print(int in, t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(&philo->data->lock_print);
	pthread_mutex_lock(&philo->data->lock_dead);
	tmp = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock_dead);
	if (!tmp)
	{
		if (in == FORK)
			printf("%lu	Philo %u has taken a fork\n",
				(get_time() - philo->data->t_start), philo->id);
		if (in == EAT)
			printf("%lu	Philo %u is eating\n",
				(get_time() - philo->data->t_start), philo->id);
		if (in == SLEEP)
			printf("%lu	Philo %u is sleeping\n",
				(get_time() - philo->data->t_start), philo->id);
		if (in == THINK)
			printf("%lu	Philo %u is thinking\n",
				(get_time() - philo->data->t_start), philo->id);
		if (in == DEATH)
			printf("%lu	Philo %u died\n",
				(get_time() - philo->data->t_start), philo->id);
	}
	pthread_mutex_unlock(&philo->data->lock_print);
}
