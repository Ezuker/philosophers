/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:00 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 02:11:26 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_eat(t_data *data)
{
	int	i;
	int	num_times_eat;
	int	num_times_eaten;

	i = 0;
	while (i < data->num_philo)
	{
		num_times_eat = data->num_times_eat;
		num_times_eaten = data->philo[i]->num_times_eaten;
		if (data->num_times_eat != -1 && num_times_eaten >= num_times_eat)
			i++;
		else
			break ;
	}
	if (i == data->num_philo)
	{
		sem_unlink(data->name_sem_dead);
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
		sem_wait(&data->philo[i]->forks);
		time_last_meal = data->philo[i]->when_last_meal;
		time_to_die = data->time_to_die;
		sem_post(&data->philo[i]->forks);
		if (time - time_last_meal > time_to_die)
		{
			mutex_print(data->philo[i], "%ld %d died\n");
			sem_unlink(data->name_sem_dead);
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
		result = check_eat(data);
		if (result == 0)
			return (NULL);
		result = check_die(data);
		if (result == 0)
			return (NULL);
	}
	return (NULL);
}
