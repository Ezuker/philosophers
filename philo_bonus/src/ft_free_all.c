/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:19:29 by bcarolle          #+#    #+#             */
/*   Updated: 2024/03/19 16:53:29 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		sem_unlink(data->philo[i]->name_sem);
		sem_close(data->philo[i]->meal);
		free(data->philo[i]->name_sem);
		free(data->philo[i]);
		i++;
	}
	sem_unlink(data->name_sem);
	sem_unlink("/philo");
	sem_unlink("write");
	sem_close(data->write);
	sem_close(data->forks);
	free(data->philo);
	free(data->name_sem);
	free(data);
}
