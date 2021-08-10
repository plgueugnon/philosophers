#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_stop
{
	do_nothing,
	one_died,
	all_have_eaten,
}				t_stop;

typedef enum	e_err
{
	no_error,
	error,
}				t_err;

typedef struct	s_arg
{
	unsigned int		nb;
	unsigned int		ms_die;
	unsigned int		ms_eat;
	unsigned int		ms_sleep;
	unsigned int		ms_start;
	unsigned int		all_meals;
	int					max_meals;
	unsigned int		stop;
	pthread_mutex_t		mtx_write;
	pthread_mutex_t		mtx_stop;
	pthread_mutex_t		mtx_time;
	pthread_mutex_t		mtx_meals;
}				t_arg;

typedef struct	s_philo
{
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	unsigned int	id;
	unsigned int	alive;
	unsigned int	ms_last_meal;
	unsigned int	nb_meals;
	unsigned int	ms_die;
	t_arg			*a;
}				t_philo;

#endif