/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:00 by bcarolle          #+#    #+#             */
/*   Updated: 2024/03/19 17:28:37 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	add_eat(t_data *data)
{
	int		i;
	// sem_t	*meal;

	i = -1;
	while (++i < data->num_philo)
	{
		if (!check_die(data))
			return (1);
		if (!check_eat(data))
			return (1);
		// sem_wait(data->open);
		// meal = sem_open(data->philo[i]->name_sem, 0);
		// sem_post(data->open);
		// sem_post(data->philo[i]->meal);
		sem_wait(data->philo[i]->meal);
		// {
		// 	printf("sem_wait error\n");
		// 	return (1);
		// }
		// sem_close(meal);
		data->philo[i]->num_times_eaten++;
		data->philo[i]->when_last_meal = ft_get_current_time() - data->start_time;
		// sem_post(data->philo[i]->meal);
	}
	return (0);
}
int	check_eat(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->num_times_eat != -1
			&& data->philo[i]->num_times_eaten >= data->num_times_eat)
			i++;
		else
			break ;
	}
	if (i == data->num_philo)
	{
		i = -1;
		sem_wait(data->write);
		printf("All philosophers have eaten %d times\n", data->num_times_eat);
		while (++i < data->num_philo)
			kill(data->philo[i]->pid, SIGKILL);
		sem_post(data->write);
		return (0);
	}
	return (1);
}

int	check_die(t_data *data)
{
	int		i;
	size_t	time;
	size_t	time_last_meal;
	size_t	time_to_die;

	i = 0;
	while (i < data->num_philo)
	{
		time = ft_get_current_time() - data->start_time;
		time_last_meal = data->philo[i]->when_last_meal;
		time_to_die = data->time_to_die;
		if (time - time_last_meal > time_to_die)
		{
			mutex_print(data->philo[i], "%ld %d died\n");
			i = -1;
			while (++i < data->num_philo)
				kill(data->philo[i]->pid, SIGKILL);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		result;

	data = (t_data *)arg;
	while (1)
	{
		result = add_eat(data);
		if (result == 1)
			return (NULL) ;
	}
	return (NULL);
}
