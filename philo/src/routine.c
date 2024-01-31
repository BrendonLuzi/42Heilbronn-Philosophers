/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:08:13 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 04:13:33 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	lock_fork(t_philo *philo, pthread_mutex_t *fork, long int start)
{
	if (!fork)
		return (msleep(philo->time_to_die + 100), 0);
	if (is_alive(philo))
	{	
		pthread_mutex_lock(fork);
		locked_print("has taken a fork", start, philo);
		return (1);
	}
	else
		return (0);
}

void	eat(t_philo *philo, long int start)
{
	if (!lock_fork(philo, philo->left_fork, start))
		return ;
	if (!lock_fork(philo, philo->right_fork, start))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (is_alive(philo))
	{
		pthread_mutex_lock(philo->personal_lock);
		philo->last_eat = get_ms_from_start(start);
		locked_print("is eating", start, philo);
		pthread_mutex_unlock(philo->personal_lock);
		if (philo->meals_count && ++philo->n_of_meals == philo->meals_count)
		{
			pthread_mutex_lock(philo->common_lock);
			*philo->philos_full += 1;
			pthread_mutex_unlock(philo->common_lock);
		}
		msleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	relax(t_philo *philo, long int start)
{
	locked_print("is sleeping", start, philo);
	msleep(philo->time_to_sleep);
	locked_print("is thinking", *philo->start, philo);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		locked_print("is thinking", *philo->start, philo);
	if (philo->id % 2 == 0)
		msleep(philo->time_to_eat / 2);
	while (is_alive(philo))
	{
		if (is_alive(philo))
			eat(philo, *philo->start);
		if (is_alive(philo))
			relax(philo, *philo->start);
	}
	return (NULL);
}
