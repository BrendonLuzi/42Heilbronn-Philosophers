/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:53:52 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 10:01:01 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_philo		*philo;
	t_data		*data;

	if (check_arguments(argc, argv) == -1)
		return (EXIT_FAILURE);
	data = create_data(argv);
	if (!data)
		return (EXIT_FAILURE);
	philo = create_philo(data);
	if (!philo)
		return (free_data(data), EXIT_FAILURE);
	threads = create_threads(philo, data);
	if (!threads)
		return (free(philo), free_data(data), EXIT_FAILURE);
	check_philos(philo, data);
	end_meal(data, philo, threads);
	return (EXIT_SUCCESS);
}
