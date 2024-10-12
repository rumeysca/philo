
#ifndef PHILOP_H
# define PHILOP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	*chopstick_r;
	pthread_mutex_t	*chopstick_l;
	int				id;
	int				meal_num;
	pthread_t		thread_id;
	unsigned long	last_eat;
}				t_philo;

typedef struct s_data
{
	unsigned long	startt;
	int				philo_num;
	unsigned long	time_to_die;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				must_eat_num;
	int				thread_index;
	int				min_max;
	pthread_mutex_t	stoper;
	pthread_mutex_t	stop;
	pthread_mutex_t	*chopstick;
	t_philo			*philo;
	int				philosopher_dead;
	int				error;
}				t_data;

void			init_thread(t_data *data);
void			init_philo(t_data *data);
void			init_mutex(t_data *data);
void			we_sleep(int time);
void			*sewing(void *a);
int				eat(t_data *data, int index);
int				sleeps(t_data *data, int index);
int				think(t_data *data, int index);
int				check_death(t_data *data, int index);
unsigned long	time_passed(t_data *data);
unsigned long	get_time(void);
void			arg_checker(char *argv[], int argc, t_data *data);
int				data_error(char *error, t_data *data);
int				status(t_data *data, int index, char *line);
void			safe_exit(t_data *data);
int				ft_isdigit(int input);
int				ft_atoi(const char *str);
void			die_status(t_data *data, int index, char *line);
int				ft_strlen(const char *str);
void			joiner(t_data *data);
int				ft_isnum(int c);
void			*one_philo(void *data_a);
int				arg_ch(char **av);
int				main_appen(char *argv[], int argc, t_data *data);
int				philo_death(t_data *data);
int				opt_arg(t_data *data);
void			unlocker(t_data *data, int index);

#endif