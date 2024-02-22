/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/22 23:53:53 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->eating_lock);
		time = ft_get_current_time() - philo->time;
		usleep(philo->parent->time_to_eat);
		philo->num_times_eaten++;
		printf("%ld %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->eating_lock);
	}
	return (arg);
}

int	philo(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->num_philo)
		if (pthread_create(&data->philo[i].philo_thread,
				NULL, &philo_routine, &data->philo[i]))
			return (ft_print_error("Failed to create thread\n"));
	i = -1;
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i].philo_thread, NULL))
			return (ft_print_error("Failed to join thread\n"));
	return (0);
}
