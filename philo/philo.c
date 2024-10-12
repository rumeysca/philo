

#include "philop.h"

void	*sewing(void *a)
{
	t_data	*data;
	int		index;

	data = (t_data *)a;
	pthread_mutex_lock(&data->stoper);
	index = data->thread_index++;
	pthread_mutex_unlock(&data->stoper);
	if (index % 2 == 0)
		usleep(100);
	while (!philo_death(data))
	{
		if (data->must_eat_num == -1 \
			|| data->philo[index].meal_num < data->must_eat_num)
		{
			if (check_death(data, index) || eat(data, index))
				break ;
			if (check_death(data, index) || sleeps(data, index))
				break ;
			if (check_death(data, index) || think(data, index))
				break ;
		}
		else
			break ;
	}
	return (NULL);
}

void	arg_checker(char *argv[], int argc, t_data *data)
{
	if (data->error == 1)
		return ;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat_num = ft_atoi(argv[5]);
		if (data->must_eat_num == 0)
			data_error("Invalid argument", data);
	}
	else
		data->must_eat_num = -1;
	if (data->philo_num <= 0 || data->philo_num > 200)
		data_error("Invalid philosopher number", data);
	if (data->time_to_die < 60 || data->eat_time < 60 || data->sleep_time < 60)
		data_error("Invalid argument", data);
}

int	main_appen(char *argv[], int argc, t_data *data)
{
	if (!(argc == 5 || argc == 6))
	{
		data->error = 1;
		return (printf("Invalid argument type\n"));
	}
	if (!arg_ch(argv))
	{
		data->error = 1;
		return (printf("Invalid argument type\n"));
	}
	return (0);
}

int	arg_ch(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (ft_isnum(av[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Memory allocation failed\n");
		return (EXIT_FAILURE);
	}
	main_appen(argv, argc, data);
	arg_checker(argv, argc, data);
	if (data->error)
	{
		safe_exit(data);
		return (EXIT_FAILURE);
	}
	init_mutex(data);
	while (!(philo_death(data)))
	{
		usleep(60);
	}
	if (philo_death(data) == 1)
		joiner(data);
	safe_exit(data);
	return (0);
}
