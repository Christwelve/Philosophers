/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/17 19:29:18 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_loop(void *arg)
{
	(void) arg;
	printf("%s\n", "Philo_loop_test");
	return (NULL);
}

int	create_threads(t_data *data)
{
	unsigned int	i;

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
		if (pthread_mutex_init(&data->philo->fork, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	set_data(int argc, char **argv, t_data *data)
{
	if (pthread_mutex_init(&data->eating, NULL))
		return (1);
	data->nbr_philos = ft_atol(argv[1]);
	data->t_to_die = ft_atol(argv[2]);
	data->t_to_eat = ft_atol(argv[3]);
	data->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->nbr_must_eat = ft_atol(argv[5]);
	// else
	// 	data->nbr_must_eat = INT_MAX;
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	while (*(++argv) != NULL)
	{
		if (is_num(*argv) || int_max(*argv))
			return (1);
	}
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

	// printf("th_id:		%i\n", (int)data.philo->thread);
	// printf("nbr_philos:	%i\n", (int)data.nbr_philos);
	// printf("%i\n", data.t_to_die);
	// printf("%i\n", data.t_to_eat);
	// printf("%i\n", data.t_to_sleep);
	// printf("%i\n", param.nbr_must_eat);
	return (0);
}
