/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/24 20:14:44 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_print(t_philo *philo, char *str)
{
	size_t			time;

	pthread_mutex_lock(&philo->parent->write_lock);
	time = ft_get_current_time() - philo->time;
	printf(str, time, philo->id);
	pthread_mutex_unlock(&philo->parent->write_lock);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	size_t	time;
	int		is_dead;

	is_dead = 0;
	philo = (t_philo *)arg;
	while (!is_dead)
	{
		pthread_mutex_lock(&philo->parent->dead_lock);
		is_dead = philo->parent->is_dead;
		pthread_mutex_unlock(&philo->parent->dead_lock);
		if (is_dead)
			break ;
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->r_fork);
		mutex_print(philo, "%ld %d has taken a fork\n");
		mutex_print(philo, "%ld %d has taken a fork\n");
		pthread_mutex_lock(&philo->eating_lock);
		philo->num_times_eaten++;
		time = ft_get_current_time() - philo->time;
		philo->timestamp_last_meal = time;
		mutex_print(philo, "%ld %d is eating\n");
		usleep(philo->parent->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->eating_lock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_lock(&philo->is_sleeping);
		mutex_print(philo, "%ld %d is sleeping\n");
		usleep(philo->parent->time_to_sleep * 1000);
		pthread_mutex_unlock(&philo->is_sleeping);
		pthread_mutex_lock(&philo->is_thinking);
		mutex_print(philo, "%ld %d is thinking\n");
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
			if (data->num_times_eat != -1
				&& data->philo[i].num_times_eaten >= data->num_times_eat)
				i++;
			else
				break ;
		}
		if (i == data->num_philo)
		{
			*status = 0;
			return (status);
		}
		i = 0;
		while (i < data->num_philo)
		{
			time = ft_get_current_time() - data->philo[i].time;
			if (time - data->philo[i].timestamp_last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_lock);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				mutex_print(&data->philo[i], "%ld %d died\n");
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
		pthread_mutex_destroy(&data->philo[i].r_fork);
		pthread_mutex_destroy(&(data->philo[i].is_sleeping));
		pthread_mutex_destroy(&(data->philo[i].is_thinking));
		pthread_mutex_destroy(&(data->philo[i].eating_lock));
		pthread_mutex_destroy(&(data->philo[i].print_lock));
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
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
	if (*status == 1 || *status == 0)
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
