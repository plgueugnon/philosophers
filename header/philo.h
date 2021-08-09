#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

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
	// unsigned int		nb_meals;
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
	unsigned int	ms_die; // test
	t_arg			*a;
}				t_philo;

// typedef struct	s_ptr
// {
// 	t_philo	*p;
// 	t_arg	*a;
// }				t_ptr;

size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
long			ft_atol(const char *str);
int				ft_isdigit(int c);
char	*ft_strjoin(char const *s1, char const *s2);

char			*ft_uitoa(unsigned int n);

void    		ft_exit(char *s_err, int err);

void			init_philo(t_philo *philo, t_arg *arg);
unsigned int	gettime(void);

void			start_philo(t_philo *philo, t_arg *arg);

void			philo_take_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

int		check_status(t_arg *arg);
void		ms_sleep(unsigned int ms_time);

void			ctrl_thread(t_philo *philo, t_arg *arg);
void			stop_show(t_philo *philo, t_arg *arg);
// int		show_must_go_on(t_philo *philo, t_arg *arg);


void			print_activity(t_philo *philo, char *status);

#endif