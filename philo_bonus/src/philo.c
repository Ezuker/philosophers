/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 04:31:16 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_eating(t_philo *philo)
{
	sem_t	*forks;
	sem_t	*meal;

	forks = sem_open(philo->parent->name_sem, 0644, philo->parent->num_philo);
	if (forks == SEM_FAILED)
	{
		perror("Child   : [sem_open_forks] Failed\n");
		return (1);
	}
	sem_wait(forks);
	sem_wait(forks);
	// sem_wait(philo->parent->open);
	meal = sem_open(philo->name_sem, 0);
	sem_post(meal);
	sem_close(meal);
	// sem_post(philo->parent->open);
	ft_usleep(philo->parent->time_to_eat);
	sem_post(forks);
	sem_post(forks);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
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
	sem_t	*forks;

	sem_unlink(data->name_sem);
	forks = sem_open(data->name_sem, O_CREAT, 0644, data->num_philo);
	sem_close(forks);
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
