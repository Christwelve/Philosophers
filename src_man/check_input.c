/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:52:51 by cmeng             #+#    #+#             */
/*   Updated: 2023/04/20 09:43:55 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	output;
	int		sign;

	i = 0;
	output = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = output * 10 + str[i] - '0';
		i++;
	}
	return (output * sign);
}

static int	int_max(char *argv)
{
	long	nbr;

	nbr = ft_atol(argv);
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (1);
	return (0);
}

static int	is_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
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
