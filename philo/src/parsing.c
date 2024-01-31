/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 05:55:41 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 07:15:27 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (philo_putstr_fd(WRONG_ARG_COUNT, 2), -1);
	if (!is_positive_integer(argv[1]))
		return (philo_putstr_fd(INVALID_ARG, 2), -1);
	if (!is_positive_integer(argv[2]))
		return (philo_putstr_fd(INVALID_ARG, 2), -1);
	if (!is_positive_integer(argv[3]))
		return (philo_putstr_fd(INVALID_ARG, 2), -1);
	if (!is_positive_integer(argv[4]))
		return (philo_putstr_fd(INVALID_ARG, 2), -1);
	if (argc == 6 && !is_positive_integer(argv[5]))
		return (philo_putstr_fd(INVALID_ARG, 2), -1);
	return (0);
}

int	is_positive_integer(char *c)
{
	long int	n;

	n = 0;
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		n *= 10;
		n += (*c - '0');
		if (n > 2147483647)
			return (0);
		c++;
	}
	return (n > 0);
}
