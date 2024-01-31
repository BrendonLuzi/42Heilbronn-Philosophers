/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:11:58 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 09:28:42 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->common_lock);
	if (!*(philo->stop))
		return (pthread_mutex_unlock(philo->common_lock), 1);
	else
		return (pthread_mutex_unlock(philo->common_lock), 0);
}

int	check_meal_count(t_data *data)
{
	pthread_mutex_lock(data->common_lock);
	if (*data->philos_full == data->philo_count)
	{
		printf("Everybody ate %d times\n", data->meals_count);
		*data->stop = 1;
		return (pthread_mutex_unlock(data->common_lock), 1);
	}
	return (pthread_mutex_unlock(data->common_lock), 0);
}

int	check_philo_death(t_philo *philo, t_data *data, long int start)
{
	int	i;
	int	time_to_die;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->personal_lock[i]);
		if (get_ms_from_start(start) - philo[i].last_eat >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->personal_lock[i]);
			pthread_mutex_lock(data->common_lock);
			*data->stop = 1;
			printf("%d\t%d\tdied\n", get_ms_from_start(start), philo[i].id);
			pthread_mutex_unlock(data->common_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->personal_lock[i]);
	}
	return (0);
}

void	check_philos(t_philo *philo, t_data *data)
{
	long int	start;

	start = *philo->start;
	while (1)
	{
		if (check_philo_death(philo, data, start) == 1)
			return ;
		if (data->meals_count && check_meal_count(data) == 1)
			return ;
	}
}

void	end_meal(t_data *data, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(threads[i], NULL) != 0)
			philo_putstr_fd(THREAD_CREATE_ERR, 2);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->personal_lock[i]);
	}
	pthread_mutex_destroy(data->common_lock);
	free_data(data);
	free(threads);
	free(philo);
}
