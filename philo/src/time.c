/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 01:06:47 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 05:50:42 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	get_current(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	get_ms_from_start(int start)
{
	return ((int)(get_current() - start));
}

void	msleep(int ms)
{
	long int	sleep_start;

	sleep_start = get_current();
	while (get_ms_from_start(sleep_start) < ms)
		usleep(100);
}
