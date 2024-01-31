/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:54:32 by bluzi             #+#    #+#             */
/*   Updated: 2023/06/29 10:05:02 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define WRONG_ARG_COUNT "Error: wrong number of arguments!\n"
# define INVALID_ARG "Error: arguments must be positive integers!\n"
# define THREAD_CREATE_ERR "Error: failed to create thread!\n"
# define ALLOC_ERROR "Error: allocation failed!\n"

typedef struct s_philo
{
	long int		*start;
	int				*stop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		last_eat;
	int				id;
	int				n_of_meals;
	int				meals_count;
	int				*philos_full;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*common_lock;
	pthread_mutex_t	*personal_lock;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*common_lock;
	pthread_mutex_t	*personal_lock;
	long int		*start;
	int				*stop;
	int				*philos_full;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_count;
	int				meals_count;
}	t_data;

void		msleep(int ms);
long int	get_current(void);
int			get_ms_from_start(int start);

void		eat(t_philo *philo, long int start);
void		relax(t_philo *philo, long int start);
void		*philo_routine(void *arg);
int			lock_fork(t_philo *philo, pthread_mutex_t *fork, long int start);

int			check_arguments(int argc, char **argv);
int			is_positive_integer(char *c);

t_philo		*create_philo(t_data *data);
t_data		*create_data(char **argv);
pthread_t	*create_threads(t_philo *philo, t_data *data);

void		check_philos(t_philo *philo, t_data *data);
int			check_philo_death(t_philo *philo, t_data *data, long int start);
int			check_meal_count(t_data *data);
int			is_alive(t_philo *philo);
void		end_meal(t_data *data, t_philo *philo, pthread_t *threads);

void		locked_print(char *action, long int start, t_philo *philo);
int			philo_atoi(char *c);
void		philo_putstr_fd(char *str, int fd);
void		*p_calloc(int count, int size);
void		free_data(t_data *data);

#endif