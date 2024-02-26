/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:36:39 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/26 15:36:39 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	struct_init_philo(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo *) * (data->num_philo + 1));
	if (!data->philo)
		return (failed_malloc());
	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->philo[i]->id = i + 1;
		data->philo[i]->parent = data;
		data->philo[i]->timestamp_last_meal = 0;
		data->philo[i]->num_times_eaten = 0;
		pthread_mutex_init(&data->philo[i]->r_fork, NULL);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (i == 0)
			data->philo[i]->l_fork = &data->philo[data->num_philo - 1]->r_fork;
		else
			data->philo[i]->l_fork = &data->philo[i - 1]->r_fork;
	}
	data->philo[i] = NULL;
	return (0);
}

int	struct_init_data(int argc, char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	if (data->num_philo < 1 || data->num_philo > 200)
		return (ft_print_error("Wrong number of philosophers\n"));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = ft_get_current_time();
	data->is_dead = 0;
	if (data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (ft_print_error("Time to die or eat or sleep is too low\n"));
	if (argc != 6)
		data->num_times_eat = -1;
	else
		data->num_times_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	if (struct_init_philo(data))
		return (1);
	return (0);
}
