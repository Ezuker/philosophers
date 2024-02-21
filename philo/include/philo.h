/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:33:41 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/21 19:38:40 by bcarolle         ###   ########.fr       */
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
	int		id;
	t_data	*parent;
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

size_t	ft_strlen(const char *str);
int		failed_malloc(void);
int		ft_atoi(const char *str);
int		ft_print_error(char *str);

#endif
