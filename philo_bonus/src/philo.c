/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/03/19 17:21:10 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	// sem_t	*forks;
	// int		haha;

	// forks = sem_open(philo->parent->name_sem, O_CREAT, 0644, philo->parent->num_philo);
	// sem_getvalue(forks, &haha);
	// printf("22 philo_eating value = %d thread id = %d\n", haha, philo->id);
	sem_wait(philo->parent->forks);
	sem_wait(philo->parent->forks);
	mutex_print(philo, "%ld %d has taken a fork\n");
	mutex_print(philo, "%ld %d has taken a fork\n");
	mutex_print(philo, "%ld %d is eating\n");
	sem_post(philo->meal);
	ft_usleep(philo->parent->time_to_eat);
	sem_post(philo->parent->forks);
	sem_post(philo->parent->forks);
	// sem_close(forks);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		philo_eating(philo);
		mutex_print(philo, "%ld %d is sleeping\n");
		ft_usleep(philo->parent->time_to_sleep);
		mutex_print(philo, "%ld %d is thinking\n");
	}
	ft_free_all(philo->parent);
	exit(0);
}

int	philo(t_data *data)
{
	int		i;
	pid_t	pid;
	int		number;
	pthread_t	monitor_thread;

	number = data->num_philo;
	sem_unlink(data->name_sem);
	data->forks = sem_open(data->name_sem, O_CREAT, 0644, number);
	// sem_close(data->forks);
	i = -1;
	while (++i < data->num_philo)
	{
		pid = fork();
		if (!pid)
			philo_routine(data->philo[i]);
		sem_wait(data->write);
		data->philo[i]->pid = pid;
		sem_post(data->write);
	}
	pthread_create(&monitor_thread, NULL, monitor, (void *)data);
	pthread_join(monitor_thread, NULL);
	return (0);
}
