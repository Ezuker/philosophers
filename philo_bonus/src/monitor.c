/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:00 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 01:25:34 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	check_eat(t_data *data)
{
	int		i;
	int		num_times_eat;
	sem_t	*meal;

	i = 0;
	num_times_eat = data->num_times_eat;
	while (i < data->num_philo)
	{
		meal = sem_open(data->philo[i]->name_sem, 0644);
		int haha = sem_getvalue(meal, &haha);
		printf("sem_getvalue = %d\n", haha);
		if (sem_wait(meal))
			data->philo[i]->num_times_eaten++;
		// printf("num_times_eat = %d\n", data->philo[i]->num_times_eaten);
		sem_close(meal);
		if (data->num_times_eat != -1
			&& data->philo[i]->num_times_eaten >= num_times_eat)
			i++;
		else
			break ;
	}
	if (i == data->num_philo)
	{
		data->is_dead = 1;
		i = -1;
		while (++i < data->num_philo)
			kill(data->philo[i]->pid, SIGKILL);
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
			data->is_dead = 1;
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
		result = check_eat(data);
		if (result == 0)
			return (NULL);
		result = check_die(data);
		if (result == 0)
			return (NULL);
	}
	return (NULL);
}
