/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/27 06:12:05 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv))
		return (printf("%s\n", RED "Invalid input!" CLEAR), 1);
	if (set_data(argc, argv, &data))
		return (printf("%s\n", RED "Setup data failed!" CLEAR),
			free_data(&data), 2);
	if (set_philo(&data))
		return (printf("%s\n", RED "Setup philo failed!" CLEAR),
			free_all(&data), 3);
	if (create_threads(&data))
		return (printf("%s\n", RED "Creating threads failed!" CLEAR),
			free_all(&data), 4);
	if (join_threads(&data))
		return (printf("%s\n", RED "Joining threads failed!" CLEAR),
			free_all(&data), 5);
	free_all(&data);
	return (0);
}
