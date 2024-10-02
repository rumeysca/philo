/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:01:41 by rcan              #+#    #+#             */
/*   Updated: 2024/10/02 19:28:18 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philop.h"

unsigned long	time_passed(t_data *data)
{
	return (get_time() - data->startt);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	we_sleep(int time)
{
	unsigned long	time_zone;

	time_zone = get_time();
	while (get_time() < time_zone + time)
		usleep(100);
}

int	ft_isdigit(int input)
{
	return (input >= '0' && input <= '9');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (sign == -1 || i != ft_strlen(str))
		return (0);
	return (num * sign);
}
