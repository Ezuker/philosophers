/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:08:55 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 13:58:48 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mutex_print(t_philo *philo, char *str)
{
	size_t			time;

	sem_wait(philo->parent->write);
	time = ft_get_current_time() - philo->parent->start_time;
	printf(str, time, philo->id);
	sem_post(philo->parent->write);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
		usleep(10);
	return (0);
}
