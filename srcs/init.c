#include "philo.h"

int		check_status(t_arg *arg)
{
		pthread_mutex_lock(&(arg->mtx_stop));
		if (arg->stop)
		{
			pthread_mutex_unlock(&(arg->mtx_stop));
			return (1);
		}
		pthread_mutex_unlock(&(arg->mtx_stop));
		return (0);
}

int		check_status2(t_philo *philo, t_arg *arg)
{
		pthread_mutex_lock(&(arg->mtx_stop));
		if (arg->stop)
		{
			pthread_mutex_unlock(&(arg->mtx_stop));
			return (1);
		}
		philo->alive = 0;
		pthread_mutex_unlock(&(arg->mtx_stop));
		return (0);
}

unsigned int	gettime(void)
{
	unsigned int	time;
	struct timeval ctime;

	time = 0;
	if (gettimeofday(&ctime, NULL))
		ft_exit("Error: fail to get time\n", error);
	time = ctime.tv_sec * 1000 + ctime.tv_usec / 1000;
	return (time);
}

void	init_philo(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	while(i < arg->nb)
	{
		philo[i].id = i + 1;
		philo[i].alive = 1;
		philo[i].ms_last_meal = arg->ms_start;
		philo[i].a = arg;
		philo[i].nb_meals = 0;
		philo[i].ms_die = arg->ms_die;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		if (i == arg->nb - 1)
			philo[i].left_fork = &philo[0].right_fork;
		else
			philo[i].left_fork = &philo[i + 1].right_fork;
		i++;
	}
}