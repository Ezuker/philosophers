/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:07 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 15:52:31 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_if_dead(t_philo *philo)
{
	sem_t *dead;

	dead = sem_open(philo->parent->name_sem_dead, 0644);
	if (dead == SEM_FAILED)
	{
		printf("Child   : [sem_open] Failed id : %d\n", philo->id);
		return (1);
	}
	return (0);
}

void	philo_eating(t_philo *philo)
{
	sem_t	*forks;

	forks = sem_open(philo->parent->name_sem, 0644, philo->parent->num_philo);
	if (forks == SEM_FAILED)
	{
		perror("Child   : [sem_open] Failed\n");
		return ;
	}
	sem_wait(forks);
	sem_wait(forks);
	if (check_if_dead(philo))
	{
		sem_post(forks);
		sem_post(forks);
		sem_close(forks);
		return ;
	}
	mutex_print(philo, "%ld %d has taken a fork\n");
	mutex_print(philo, "%ld %d has taken a fork\n");
	sem_wait(&philo->forks);
	philo->num_times_eaten++;
	philo->when_last_meal = ft_get_current_time() - philo->parent->start_time;
	sem_post(&philo->forks);
	printf("when last meal%ld\n", philo->when_last_meal);
	if (check_if_dead(philo))
	{
		sem_post(forks);
		sem_post(forks);
		sem_close(forks);
		return ;
	}
	mutex_print(philo, "%ld %d is eating\n");
	ft_usleep(philo->parent->time_to_eat);
	sem_post(forks);
	sem_post(forks);
	sem_close(forks);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	pid_t	pid;

	philo = (t_philo *)arg;
	pid = fork();
	if (!pid)
	{
		while (1)
		{
			if (philo->id % 2 == 0)
				ft_usleep(10);
			if (check_if_dead(philo))
				break ;
			philo_eating(philo);
			if (check_if_dead(philo))
				break ;
			mutex_print(philo, "%ld %d is sleeping\n");
			ft_usleep(philo->parent->time_to_sleep);
			if (check_if_dead(philo))
				break ;
			mutex_print(philo, "%ld %d is thinking\n");
		}
		ft_free_all(philo->parent);
		exit(0);
	}
	waitpid(pid, NULL, 0);
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
