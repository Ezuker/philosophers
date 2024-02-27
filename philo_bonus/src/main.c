/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:34:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 01:46:39 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;
	sem_t	*forks;
	sem_t	*dead;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Wrong number of arguments\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (failed_malloc());
	if (struct_init_data(argc, argv, data))
	{
		free(data);
		return (1);
	}
	sem_unlink(data->name_sem);
	forks = sem_open(data->name_sem, O_CREAT, 0644, data->num_philo);
	sem_close(forks);
	sem_unlink(data->name_sem_dead);
	dead = sem_open(data->name_sem_dead, O_CREAT, 0644, 1);
	sem_close(dead);
	philo(data);
	ft_free_all(data);
	return (0);
}
