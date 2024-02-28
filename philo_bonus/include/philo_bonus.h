/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:33:41 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 01:16:45 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				num_times_eaten;
	size_t			when_last_meal;
	pthread_t		philo_thread;
	pid_t			pid;
	char			*name_sem;
	sem_t			*meal;
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
	char			*name_sem;
	char			*name_sem_dead;
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
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int number);
char	*ft_strdup(char *s1);

// Philo
int		philo(t_data *data);
void	*monitor(void *arg);
int		check_die(t_data *data);
int		check_eat(t_data *data);

#endif
