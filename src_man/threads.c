/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:13:37 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/26 22:14:07 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_threads(t_data *data)
{
	unsigned int	i;

	data->t_start = get_time();
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				&philo_loop, &data->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->death_thread, NULL, &survival_loop, data->philo))
		return (1);
	return (0);
}

int	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(data->death_thread, NULL))
		return (1);
	return (0);
}
