/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 14:23:14 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_eating(t_philo *philo)
{
	// sem_t	*forks;

	// forks = sem_open(philo->parent->name_sem, 0);
	// if (forks == SEM_FAILED)
	// {
	// 	perror("Child   : [sem_open_forks] Failed\n");
	// 	return (1);
	// }
	if (sem_wait(philo->parent->forks) < 0)
	{
		perror("Child   : [sem_wait_forks] Failed\n");
		return (1);
	}
	if (sem_wait(philo->parent->forks) < 0)
	{
		perror("Child   : [sem_wait_forks] Failed\n");
		return (1);
	}
	// sem_wait(forks);
	// sem_wait(forks);
	// sem_wait(philo->parent->open);
	// meal = sem_open(philo->name_sem, 0);
	// sem_post(philo->parent->open);
	sem_post(philo->meal);
	// sem_close(meal);
	ft_usleep(philo->parent->time_to_eat);
	sem_post(philo->parent->forks);
	sem_post(philo->parent->forks);
	// sem_close(forks);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		// if (philo->id % 2)
		// 	ft_usleep(10);
		if (philo_eating(philo))
			break ;
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
	// sem_t	*forks;

	sem_unlink(data->name_sem);
	data->forks = sem_open(data->name_sem, O_CREAT, 0644, data->num_philo);
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
	return (0);
}
