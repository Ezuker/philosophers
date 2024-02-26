/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:33:41 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/26 21:55:30 by bcarolle         ###   ########.fr       */
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
	int				id;
	int				num_times_eaten;
	size_t			when_last_meal;
	pthread_t		philo_thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	t_data			*parent;
}				t_philo;

typedef struct s_data
{
	int				num_philo;
	int				num_times_eat;
	int				is_dead;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	t_philo			**philo;
}				t_data;

// Parsing + init
int		struct_init_philo(t_data *data);
int		struct_init_data(int argc, char **argv, t_data *data);
int		failed_malloc(void);

// Utils
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_print_error(char *str);
size_t	ft_get_current_time(void);
void	ft_free_all(t_data *data);
void	mutex_print(t_philo *philo, char *str);
int		ft_usleep(size_t milliseconds);

// Philo
int		philo(t_data *data);
void	*monitor(void *arg);

#endif
