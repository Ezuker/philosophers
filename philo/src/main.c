/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:34:30 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/24 02:23:43 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;

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
	if (philo(data))
	{
		return (1);
	}
	return (0);
}
