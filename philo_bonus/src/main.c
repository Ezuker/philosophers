/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:34:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/28 00:13:50 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	monitor_thread;

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
	pthread_create(&monitor_thread, NULL, monitor, (void *)data);
	philo(data);
	pthread_join(monitor_thread, NULL);
	ft_free_all(data);
	return (0);
}
