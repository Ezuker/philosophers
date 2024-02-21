/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:34:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/21 19:40:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	struct_init(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->num_philo = ft_atoi(argv[1]);
	if (data->num_philo < 1 || data->num_philo > 200)
		return (ft_print_error("Wrong number of philosophers\n"));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (ft_print_error("Time to die or eat or sleep is too low\n"));
	if (argc != 6)
		data->num_times_eat = -1;
	else
		data->num_times_eat = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->num_philo + 1);
	while (i < data->num_philo)
	{
		data->philo[i].id = i;
		data->philo[i].parent = data;
		i++;
	}
	data->philo[i].id = -1;
	return (0);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (failed_malloc());
	struct_init(argc, argv, data);
	printf("num_philo: %d\n", data->philo[0].id);
}
