/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/13 15:17:07 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	if (check_input(argc, argv))
		return (printf("%s\n", "Invalid input!"), 1);


	return (0);
}
