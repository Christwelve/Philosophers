/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/26 22:18:50 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void check(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char **argv)
{
	t_data	data;

	// atexit(check);
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
	free_all(&data);
	return (0);
}
