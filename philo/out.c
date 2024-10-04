/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:02:08 by rcan              #+#    #+#             */
/*   Updated: 2024/10/03 19:59:58 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philop.h"

int	status(t_data *data, int index, char *line)
{
	pthread_mutex_lock(&data->stoper);
	if (data->philosopher_dead)
	{
		pthread_mutex_unlock(&data->stoper);
		return (1);
	}
	pthread_mutex_unlock(&data->stoper);
	pthread_mutex_lock(&data->stoper);
	printf("%lu\t%d %s\n", time_passed(data), data->philo[index].id, line);
	pthread_mutex_unlock(&data->stoper);
	return (0);
}

void	safe_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->chopstick)
	{
		while (i < data->philo_num)
		{
			pthread_mutex_destroy(&data->chopstick[i]);
			i++;
		}
		free(data->chopstick);
	}
	if (data->philo)
	{
		free(data->philo);
	}
	free(data);
}

int	data_error(char *error, t_data *data)
{
	data->error = 1;
	printf("%s\n", error);
	return (1);
}

int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}
