/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/26 16:28:43 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

// int	is_philo_dead(t_philo *philo, int i)
// {
// 	if (((get_time() - philo[i].t_last_eat)) > philo->data->t_to_die)
// 		return (1);
// 	return (0);
// }

void	*survival_loop(void *arg)
{
	t_philo			*philo;
	unsigned int	i;
	unsigned int	tmp;

	philo = arg;
	i = 0;
	tmp = 0;
	// while (!philo->data->dead)
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
		i++;
		if (i == philo->data->nbr_philos - 1)
			i = 0;
		pthread_mutex_lock(&philo->data->lock_dead);
		tmp = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock_dead);

	}
	return (NULL);
}

void	*philo_loop(void *arg)
{
	t_philo			*philo;
	unsigned int	tmp;

	philo = arg;
	tmp = 0;
	if (philo->id % 2 == 0)
	{
		print(THINK, philo);
		msleep(5);
	}
	while (!philo_saturated(philo) && !tmp)
	{
		pthread_mutex_lock(&philo->fork);
		print(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		print(L_FORK, philo);
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
	return (NULL);
}

// void	*survival_loop(void *arg)
// {
// 	t_philo			*philo;
// 	unsigned int	i;

// 	philo = arg;
// 	i = 0;
// 	while (!philo->data->dead)
// 	{
// 		pthread_mutex_lock(&philo->lock_last_eat);
// 		if ((get_time() - philo[i].t_last_eat) > philo->data->t_to_die)
// 		{
// 			print(DEATH, philo);
// 			philo->data->dead = 1;
// 		}
// 		pthread_mutex_unlock(&philo->lock_last_eat);
// 		i++;
// 		if (i == philo->data->nbr_philos - 1)
// 			i = 0;
// 	}
// 	return (NULL);
// }


// void	*philo_loop(void *arg)
// {
// 	t_philo	*philo;

// 	philo = arg;
// 	if (philo->id % 2 == 0)
// 	{
// 		print(THINK, philo);
// 		msleep(5);
// 	}
// 	while (!philo_saturated(philo) && !philo->data->dead)
// 	{
// 		pthread_mutex_lock(&philo->fork);
// 		print(FORK, philo);
// 		pthread_mutex_lock(philo->l_fork);
// 		print(L_FORK, philo);
// 		print(EAT, philo);
// 		philo->count_eat++;
// 		pthread_mutex_lock(&philo->lock_last_eat);
// 		philo->t_last_eat = get_time();
// 		pthread_mutex_unlock(&philo->lock_last_eat);
// 		msleep(philo->data->t_to_eat);
// 		pthread_mutex_unlock(&philo->fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 		print(SLEEP, philo);
// 		msleep(philo->data->t_to_sleep);
// 		print(THINK, philo);
// 	}
// 	return (NULL);
// }

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
	// if (pthread_create(&data->philo->thread, NULL, &survival_loop, data->philo))
		// return (1);
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
		if (pthread_detach(data->philo[i].thread))
			return (1);
		// if (pthread_join(data->philo[i].thread, NULL))
		// 	return (1);
		i++;
	}
	// if (pthread_detach(data->death_thread))
	// 	return (1);
	if (pthread_join(data->death_thread, NULL))
		return (1);
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
	if (pthread_mutex_init(&data->lock_dead, NULL))
		return (1);
	return (0);
}

// void	free_all(t_data *data)
// {
// 	pthread_mutex_destroy(&data->philo->fork);
// 	pthread_mutex_destroy(data->philo->l_fork);
// 	free(data->philo);
// }

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
		return (printf("%s\n", RED "Joining threads failed!" CLEAR), 5);
	// free_all(&data);
	pthread_mutex_destroy(&data.philo->fork);
	pthread_mutex_destroy(data.philo->l_fork);
	free(data.philo);
	return (0);
}
