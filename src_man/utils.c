/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:45:19 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/20 09:46:44 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

void	print(int in, t_philo *philo)
{
	if (in == FORK)
		printf("%lu	Philo %u has taken a fork\n",
			(get_time() - philo->data->t_start), philo->id);
	if (in == EAT)
		printf("%lu	Philo %u has eaten\n",
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