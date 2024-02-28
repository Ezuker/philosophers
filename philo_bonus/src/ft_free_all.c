/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:19:29 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 04:31:33 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		free(data->philo[i]->name_sem);
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	sem_unlink(data->name_sem);
	free(data->name_sem);
	// sem_close(data->open);
	sem_close(data->write);
	sem_unlink("write");
	// sem_unlink("open");
	free(data);
}
