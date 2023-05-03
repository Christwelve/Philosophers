/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:16:30 by cmeng             #+#    #+#             */
/*   Updated: 2023/05/02 08:06:51 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	set_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (data->philo == NULL)
		return (1);
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].count_eat = 0;
		data->philo[i].thread = 0;
		data->philo[i].data = data;
		data->philo[i].t_last_eat = get_time();
		if (pthread_mutex_init(&data->philo->lock_count_eat, NULL))
			return (1);
		if (pthread_mutex_init(&data->philo->lock_last_eat, NULL))
			return (1);
		if (pthread_mutex_init(&data->philo[i].fork, NULL))
			return (1);
		if (i > 0)
			data->philo[i].l_fork = &data->philo[i - 1].fork;
		i++;
	}
	data->philo[0].l_fork = &data->philo[i - 1].fork;
	return (0);
}

int	set_data(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->t_to_die = ft_atol(argv[2]);
	data->t_to_eat = ft_atol(argv[3]);
	data->t_to_sleep = ft_atol(argv[4]);
	data->dead = 0;
	if (argc == 6)
		data->nbr_must_eat = ft_atol(argv[5]);
	else
		data->nbr_must_eat = 0;
	if (pthread_mutex_init(&data->lock_time, NULL))
		return (1);
	if (pthread_mutex_init(&data->lock_dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->lock_print, NULL))
		return (1);
	return (0);
}
