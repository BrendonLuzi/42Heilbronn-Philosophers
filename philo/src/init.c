/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:13:23 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 09:52:20 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo	*create_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = p_calloc(data->philo_count, sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].meals_count = data->meals_count;
		philo[i].id = i + 1;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		if (data->philo_count == 1)
			philo[i].right_fork = NULL;
		philo[i].personal_lock = &data->personal_lock[i];
		philo[i].common_lock = data->common_lock;
		philo[i].start = data->start;
		philo[i].stop = data->stop;
		philo[i].philos_full = data->philos_full;
	}
	return (philo);
}

int	allocate_data(t_data *data)
{
	data->forks = p_calloc(data->philo_count, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	data->personal_lock = p_calloc(data->philo_count, sizeof(pthread_mutex_t));
	if (!data->personal_lock)
		return (0);
	data->common_lock = p_calloc(1, sizeof(pthread_mutex_t));
	if (!data->common_lock)
		return (0);
	data->start = p_calloc(1, sizeof(long int));
	if (!data->start)
		return (0);
	data->stop = p_calloc(1, sizeof(int));
	if (!data->stop)
		return (0);
	data->philos_full = p_calloc(1, sizeof(int));
	if (!data->philos_full)
		return (0);
	return (1);
}

t_data	*create_data(char **argv)
{
	t_data	*data;
	int		i;

	i = -1;
	data = p_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_count = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		data->meals_count = philo_atoi(argv[5]);
	if (!allocate_data(data))
		return (free_data(data), NULL);
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->personal_lock[i], NULL);
	}
	pthread_mutex_init(data->common_lock, NULL);
	return (data);
}

pthread_t	*create_threads(t_philo *philo, t_data *data)
{
	pthread_t	*threads;
	int			i;

	threads = p_calloc(data->philo_count, sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = -1;
	*data->start = get_current();
	while (++i < data->philo_count)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, &philo[i]) != 0)
			return (philo_putstr_fd(THREAD_CREATE_ERR, 2), free(threads), NULL);
	}
	return (threads);
}
