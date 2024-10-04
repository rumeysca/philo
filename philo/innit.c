/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:58:53 by rcan              #+#    #+#             */
/*   Updated: 2024/10/03 19:31:53 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philop.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		data_error("Memory allocation failed", data);
	while (i < data->philo_num)
	{
		data->philo[i].last_eat = get_time();
		data->philo[i].meal_num = 0;
		data->philo[i].id = i + 1;
		data->min_max = 0;
		data->philo[i].chopstick_l = &data->chopstick[i];
		data->philo[i].chopstick_r = &data->chopstick[(i + 1) \
			% data->philo_num];
		i++;
	}
	data->philosopher_dead = 0;
	init_thread(data);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->chopstick = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->chopstick)
		data_error("Memory allocation failed", data);
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->chopstick[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->stoper, NULL);
	init_philo(data);
}

void	*one_philo(void *data_a)
{
	t_data	*data;

	data = (t_data *)data_a;
	status(data, 0, "has taken fork");
	we_sleep(data->time_to_die);
	die_status(data, 0, "died");
	data->philosopher_dead = 1;
	return (NULL);
}

void	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->startt = get_time();
	if (data->philo_num == 1)
	{
		pthread_create(&data->philo[0].thread_id, NULL, &one_philo, data);
		return ;
	}
	while (i < data->philo_num && !data->philosopher_dead)
	{
		pthread_create(&data->philo[i].thread_id, NULL, sewing, (void *)data);
		i++;
	}
}

void	joiner(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&data->stoper);
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_unlock(&data->stoper);
	pthread_mutex_destroy(&data->stoper);
}
