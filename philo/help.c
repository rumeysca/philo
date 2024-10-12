
#include "philop.h"

int	eat(t_data *data, int index)
{
	pthread_mutex_lock(data->philo[index].chopstick_l);
	if (check_death(data, index))
	{
		pthread_mutex_unlock(data->philo[index].chopstick_l);
		return (1);
	}
	status(data, index, "has taken a fork");
	pthread_mutex_lock(data->philo[index].chopstick_r);
	status(data, index, "has taken a fork");
	if (check_death(data, index))
	{
		unlocker(data, index);
		return (1);
	}
	status(data, index, "is eating");
	data->philo[index].last_eat = get_time();
	data->philo[index].meal_num++;
	if (data->philo[index].meal_num == data->must_eat_num)
		data->min_max++;
	we_sleep(data->eat_time);
	if (data->min_max == data->philo_num)
		return (opt_arg(data));
	unlocker(data, index);
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
		if (!philo_death(data))
		{
			pthread_mutex_lock(&data->stoper);
			if (philo_death(data))
			{
				pthread_mutex_unlock(&data->stoper);
				return (1);
			}
			die_status(data, index, "died");
			pthread_mutex_lock(&data->stop);
			data->philosopher_dead = 1;
			pthread_mutex_unlock(&data->stop);
		}
		return (1);
	}
	return (0);
}

void	die_status(t_data *data, int index, char *line)
{
	printf("%lu\t%d %s\n", time_passed(data), data->philo[index].id, line);
}
