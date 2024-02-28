/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 01:38:32 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_if_dead(t_philo *philo)
{
	sem_t	*dead;

	dead = sem_open(philo->parent->name_sem_dead, 0644);
	if (dead == SEM_FAILED)
	{
		printf("Child   : [sem_open_dead] Failed id : %d\n", philo->id);
		return (1);
	}
	return (0);
}

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
	if (check_if_dead(philo))
	{
		sem_post(forks);
		sem_post(forks);
		sem_close(forks);
		return (1);
	}
	mutex_print(philo, "%ld %d has taken a fork\n");
	mutex_print(philo, "%ld %d has taken a fork\n");
	meal = sem_open(philo->name_sem, 0);
	int haha = sem_getvalue(meal, &haha);
	printf("%s\n", philo->name_sem);
	printf("sem_getvalue = %d\n", haha);
	philo->num_times_eaten++;
	philo->when_last_meal = ft_get_current_time() - philo->parent->start_time;
	sem_post(meal);
	haha = sem_getvalue(meal, &haha);
	printf("sem_getvalue = %d\n", haha);
	sem_close(meal);
	if (check_if_dead(philo))
	{
		sem_post(forks);
		sem_post(forks);
		sem_close(forks);
		return (1);
	}
	mutex_print(philo, "%ld %d is eating\n");
	ft_usleep(philo->parent->time_to_eat);
	sem_post(forks);
	sem_post(forks);
	sem_close(forks);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0)
			ft_usleep(10);
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
	sem_t	*dead;

	sem_unlink(data->name_sem);
	forks = sem_open(data->name_sem, O_CREAT, 0644, data->num_philo);
	sem_close(forks);
	sem_unlink(data->name_sem_dead);
	dead = sem_open(data->name_sem_dead, O_CREAT, 0644, 1);
	sem_close(dead);
	i = -1;
	while (++i < data->num_philo)
	{
		pid = fork();
		if (!pid)
			philo_routine(data->philo[i]);
		data->philo[i]->pid = pid;
	}
	return (0);
}
