

#include "philop.h"

int	philo_death(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->philosopher_dead == 1)
	{
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	return (0);
}

int	opt_arg(t_data *data)
{
	if (!philo_death(data))
	{
		pthread_mutex_lock(&data->stoper);
		if (philo_death(data))
		{
			pthread_mutex_unlock(&data->stoper);
			return (1);
		}
		pthread_mutex_lock(&data->stop);
		data->philosopher_dead = 1;
		pthread_mutex_unlock(&data->stop);
	}
	return (1);
}

void	unlocker(t_data *data, int index)
{
	pthread_mutex_unlock(data->philo[index].chopstick_r);
	pthread_mutex_unlock(data->philo[index].chopstick_l);
}
