/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:36:39 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/27 02:09:52 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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
		if (!data->philo[i])
			return (failed_malloc());
		data->philo[i]->id = i + 1;
		data->philo[i]->parent = data;
		data->philo[i]->when_last_meal = 0;
		data->philo[i]->num_times_eaten = 0;
		sem_init(&data->philo[i]->forks, 1, 1);
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
	data->name_sem = ft_strdup("philo");
	if (!data->name_sem)
		return (failed_malloc());
	data->name_sem_dead = ft_strdup("philo_dead");
	if (!data->name_sem_dead)
		return (failed_malloc());
	if (struct_init_philo(data))
		return (1);
	return (0);
}
