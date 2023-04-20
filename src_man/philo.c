/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/20 09:47:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		print(THINK, philo);
		usleep(5000);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		print(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		print(FORK, philo);
		print(EAT, philo);
		philo->count_eat++;
		philo->t_last_eat = get_time();
		usleep(philo->data->t_to_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->fork);
		print(SLEEP, philo);
		usleep(philo->data->t_to_sleep * 1000);
		print(THINK, philo);
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(&data->philo->thread[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	unsigned int	i;

	data->t_start = get_time();
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_loop, &data->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	set_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (data->philo == NULL)
		return (1);
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i;
		data->philo[i].count_eat = 0;
		data->philo[i].thread = 0;
		data->philo[i].data = data;
		if (i > 0)
			data->philo[i].l_fork = &data->philo[i - 1].fork;
		if (pthread_mutex_init(&data->philo->fork, NULL))
			return (1);
		i++;
	}
	data->philo[0].l_fork = &data->philo[i].fork;
	return (0);
}

int	set_data(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->t_to_die = ft_atol(argv[2]);
	data->t_to_eat = ft_atol(argv[3]);
	data->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->nbr_must_eat = ft_atol(argv[5]);
	// else
	// 	data->nbr_must_eat = INT_MAX;
	// if (pthread_mutex_init(&data->eating, NULL))
	// 	return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv))
		return (printf("%s\n", RED "Invalid input!" CLEAR), 1);
	if (set_data(argc, argv, &data))
		return (printf("%s\n", RED "Setup data failed!" CLEAR), 2);
	if (set_philo(&data))
		return (printf("%s\n", RED "Setup philo failed!" CLEAR), 3);
	if (create_threads(&data))
		return (printf("%s\n", RED "Creating threads failed!" CLEAR), 4);
	if (join_threads(&data))
		return (printf("%s\n", RED "Joining threads failed!" CLEAR), 4);

	// printf("th_id:		%i\n", (int)data.philo->thread);
	// printf("nbr_philos:	%i\n", (int)data.nbr_philos);
	// printf("%i\n", data.t_to_die);
	// printf("%i\n", data.t_to_eat);
	// printf("%i\n", data.t_to_sleep);
	// printf("%i\n", param.nbr_must_eat);
	// sleep(2);
	// printf("test: %i\n", get_time());
	// printf("diff: %i\n", get_time() - data.t_start);

	free(data.philo);
	return (0);
}
