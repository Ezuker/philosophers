/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/22 00:13:21 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo id: %d\n", philo->id);
	printf("philo_routine\n");
	return (arg);
}

int	philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		if (pthread_create(&data->philo[i].philo_thread,
				NULL, &philo_routine, &data->philo[i]))
			return (ft_print_error("Failed to create thread\n"));
	i = -1;
	//pthread_join waits for the thread specified by thread to terminate
	//we can pass arg to join
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i].philo_thread, NULL))
			return (ft_print_error("Failed to join thread\n"));
	return (0);
}
