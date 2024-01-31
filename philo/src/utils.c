/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:14:07 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 09:51:30 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	locked_print(char *action, long int start, t_philo *philo)
{
	pthread_mutex_lock(philo->common_lock);
	if (!*philo->stop)
		printf("%d\t%d\t%s\n", get_ms_from_start(start), philo->id, action);
	pthread_mutex_unlock(philo->common_lock);
}

int	philo_atoi(char *c)
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
	return (n);
}

void	philo_putstr_fd(char *str, int fd)
{
	while (str && *str)
		write(fd, str++, 1);
}

void	*p_calloc(int count, int size)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (philo_putstr_fd(ALLOC_ERROR, 2), NULL);
	while (i < count * size)
		ptr[i++] = 0;
	return ((void *)ptr);
}

void	free_data(t_data *data)
{
	if (data && data->forks)
		free(data->forks);
	if (data && data->personal_lock)
		free(data->personal_lock);
	if (data && data->common_lock)
		free(data->common_lock);
	if (data && data->start)
		free(data->start);
	if (data && data->stop)
		free(data->stop);
	if (data && data->philos_full)
		free(data->philos_full);
	if (data)
		free(data);
}
