/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:00 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/26 17:44:13 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	size_t	time;
	size_t	time_last_meal;
	size_t	time_to_die;

	int		num_times_eat;
	int		num_times_eaten;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->write_lock);
			num_times_eat = data->num_times_eat;
			num_times_eaten = data->philo[i]->num_times_eaten;
			pthread_mutex_unlock(&data->write_lock);
			if (data->num_times_eat != -1
				&& num_times_eaten >= num_times_eat)
				i++;
			else
				break ;
		}
		if (i == data->num_philo)
		{
			pthread_mutex_lock(&data->dead_lock);
			pthread_mutex_lock(&data->write_lock);
			printf("All philosophers have eaten enough\n");
			pthread_mutex_unlock(&data->write_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		i = 0;
		while (i < data->num_philo)
		{
			time = ft_get_current_time() - data->start_time;
			pthread_mutex_lock(&data->write_lock);
			time_last_meal = data->philo[i]->timestamp_last_meal;
			time_to_die = data->time_to_die;
			pthread_mutex_unlock(&data->write_lock);
			if (time - time_last_meal > time_to_die)
			{
				pthread_mutex_lock(&data->dead_lock);
				mutex_print(data->philo[i], "%ld %d died\n");
				data->is_dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
