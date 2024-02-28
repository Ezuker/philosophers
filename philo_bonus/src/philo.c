/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 16:16:45 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	sem_t	*forks;
	int		haha;

	forks = sem_open(philo->parent->name_sem, O_CREAT, 0644, philo->parent->num_philo);
	sem_getvalue(forks, &haha);
	printf("22 philo_eating value = %d thread id = %d\n", haha, philo->id);
	sem_wait(forks);
	sem_wait(forks);
	sem_getvalue(forks, &haha);
	sem_post(philo->meal);
	printf("31 philo_eating value = %d thread id = %d\n", haha, philo->id);
	ft_usleep(philo->parent->time_to_eat);
	sem_post(forks);
	sem_post(forks);
	sem_close(forks);
}

void	philo_routine(t_philo *philo)
{
	// printf("Thread %d entered\n", philo->id);
	while (1)
	{
		// if (philo->id % 2 && philo->parent->num_philo % 2)
		// 	ft_usleep(5);
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

	number = data->num_philo;
	sem_unlink(data->name_sem);
	data->forks = sem_open(data->name_sem, O_CREAT, 0644, number);
	sem_close(data->forks);
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
	return (0);
}
