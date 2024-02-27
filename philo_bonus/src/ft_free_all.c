/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:19:29 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 01:49:11 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	free(data->name_sem);
	free(data->name_sem_dead);
	free(data);
}
