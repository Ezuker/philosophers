/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:54:59 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/26 22:15:49 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	failed_malloc(void)
{
	write(2, "malloc failed\n", 14);
	return (1);
}

int	ft_print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
