/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:05:51 by rcan              #+#    #+#             */
/*   Updated: 2024/10/03 19:33:43 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philop.h"

int	eat(t_data *data, int index)
{
	pthread_mutex_lock(data->philo[index].chopstick_l);
	status(data, index, "has taken a fork");
	pthread_mutex_lock(data->philo[index].chopstick_r);
	status(data, index, "has taken a fork");
	if (check_death(data, index))
	{
		pthread_mutex_unlock(data->philo[index].chopstick_r);
		pthread_mutex_unlock(data->philo[index].chopstick_l);
		return (1);
	}
	status(data, index, "is eating");
	data->philo[index].last_eat = get_time();
	data->philo[index].meal_num++;
	if (data->philo[index].meal_num == data->must_eat_num)
		data->min_max++;
	we_sleep(data->eat_time);
	if (data->min_max == data->philo_num)
	{
		pthread_mutex_lock(&data->stoper);
		data->philosopher_dead = 1;
		return (1);
	}
	pthread_mutex_unlock(data->philo[index].chopstick_r);
	pthread_mutex_unlock(data->philo[index].chopstick_l);
	return (0);
}

int	sleeps(t_data *data, int index)
{
	status(data, index, "is sleeping");
	we_sleep(data->sleep_time);
	return (0);
}

int	think(t_data *data, int index)
{
	status(data, index, "is thinking");
	return (0);
}

int	check_death(t_data *data, int index)
{
	unsigned long	elapsed_time;

	elapsed_time = get_time() - data->philo[index].last_eat;
	if (elapsed_time > data->time_to_die)
	{
		if (!data->philosopher_dead)
		{
			pthread_mutex_lock(&data->stoper);
			if (data->philosopher_dead)
			{
				pthread_mutex_unlock(&data->stoper);
				return (1);
			}
			die_status(data, index, "died");
			data->philosopher_dead = 1;
		}
		return (1);
	}
	return (0);
}

void	die_status(t_data *data, int index, char *line)
{
	printf("%lu\t%d %s\n", time_passed(data), data->philo[index].id, line);
}
