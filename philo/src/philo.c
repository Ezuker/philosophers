/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 00:45:47 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->parent->dead_lock);
	is_dead = philo->parent->is_dead;
	pthread_mutex_unlock(&philo->parent->dead_lock);
	return (is_dead);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	if (check_if_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		return ;
	}
	mutex_print(philo, "%ld %d has taken a fork\n");
	mutex_print(philo, "%ld %d has taken a fork\n");
	pthread_mutex_lock(&philo->parent->write_lock);
	philo->num_times_eaten++;
	philo->when_last_meal = ft_get_current_time() - philo->parent->start_time;
	pthread_mutex_unlock(&philo->parent->write_lock);
	if (check_if_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		return ;
	}
	mutex_print(philo, "%ld %d is eating\n");
	ft_usleep(philo->parent->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		is_dead;

	is_dead = 0;
	philo = (t_philo *)arg;
	while (!is_dead)
	{
		if (philo->id % 2 == 0)
			ft_usleep(5);
		if (check_if_dead(philo))
			return (arg);
		philo_eating(philo);
		if (check_if_dead(philo))
			return (arg);
		mutex_print(philo, "%ld %d is sleeping\n");
		ft_usleep(philo->parent->time_to_sleep);
		if (check_if_dead(philo))
			return (arg);
		mutex_print(philo, "%ld %d is thinking\n");
	}
	return (arg);
}

int	philo(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	while (++i < data->num_philo)
		if (pthread_create(&data->philo[i]->philo_thread,
				NULL, &philo_routine, data->philo[i]))
			return (ft_print_error("Failed to create thread\n"));
	ft_usleep(5);
	if (pthread_create(&monitor_thread, NULL, &monitor, data))
		return (ft_print_error("Failed to create thread\n"));
	i = -1;
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i]->philo_thread, NULL))
			return (ft_print_error("Failed to join thread\n"));
	ft_usleep(5);
	if (pthread_join(monitor_thread, NULL))
		return (ft_print_error("Failed to join thread\n"));
	return (0);
}
