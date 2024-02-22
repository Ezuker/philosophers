/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:33:41 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/22 19:41:20 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				id;
	size_t			timestamp_last_meal;
	int				num_times_eaten;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	is_sleeping;
	pthread_mutex_t	is_thinking;
	t_data			*parent;
}				t_philo;

typedef struct s_data
{
	int		num_philo;
	int		num_times_eat;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	t_philo	*philo;
}				t_data;

// Parsing + init
int		struct_init_philo(t_data *data);
int		struct_init_data(int argc, char **argv, t_data *data);
int		failed_malloc(void);

// Utils
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_print_error(char *str);

// Philo
int		philo(t_data *data);

#endif
