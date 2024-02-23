/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/23 23:58:35 by bcarolle         ###   ########.fr       */
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
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		time = ft_get_current_time() - philo->time;
		printf("%ld %d has taken a fork\n", time, philo->id);
		printf("%ld %d has taken a fork\n", time, philo->id);
		pthread_mutex_lock(&philo->eating_lock);
		philo->num_times_eaten++;
		philo->timestamp_last_meal = time;
		printf("%ld %d is eating\n", time, philo->id);
		usleep(philo->parent->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->eating_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		
		pthread_mutex_lock(&philo->is_sleeping);
		time = ft_get_current_time() - philo->time;
		printf("%ld %d is sleeping\n", time, philo->id);
		usleep(philo->parent->time_to_sleep * 1000);
		pthread_mutex_unlock(&philo->is_sleeping);
		
		pthread_mutex_lock(&philo->is_thinking);
		time = ft_get_current_time() - philo->time;
		printf("%ld %d is thinking\n", time, philo->id);
		pthread_mutex_unlock(&philo->is_thinking);
	}
	return (arg);
}

void	*monitor(void *arg)
{
	int		*status;
	t_data	*data;
	int		i;
	size_t	time;

	data = (t_data *)arg;
	status = malloc(sizeof(int));
	*status = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			time = ft_get_current_time() - data->philo[i].time;
			if (time - data->philo[i].timestamp_last_meal > data->time_to_die)
			{
				data->is_dead = 1;
				printf("%ld %d died\n", time, data->philo[i].id);
				*status = 1;
				return (status);
			}
			i++;
		}
	}
	return (status);
}

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->philo[i].eating_lock);
		pthread_mutex_destroy(&data->philo[i].right_fork);
		pthread_mutex_destroy(&data->philo[i].is_sleeping);
		pthread_mutex_destroy(&data->philo[i].is_thinking);
		i++;
	}
	free(data->philo);
	free(data);
}

int	philo(t_data *data)
{
	int			i;
	int			*status;
	pthread_t	monitor_thread;

	i = -1;
	if (pthread_create(&monitor_thread, NULL, &monitor, data))
		return (ft_print_error("Failed to create thread\n"));
	while (++i < data->num_philo)
		if (pthread_create(&data->philo[i].philo_thread,
				NULL, &philo_routine, &data->philo[i]))
			return (ft_print_error("Failed to create thread\n"));
	i = -1;
	if (pthread_join(monitor_thread, (void **)&status))
		return (ft_print_error("Failed to join thread\n"));
	if (*status == 1)
	{
		ft_free_all(data);
		free(status);
		return (1);
	}
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i].philo_thread, NULL))
			return (ft_print_error("Failed to join thread\n"));
	return (0);
}
