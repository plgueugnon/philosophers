#include "philo.h"

void    ft_exit(char *s_err, int err)
{
	if (!err)
	{
		ft_putstr_fd(s_err, 1);
		exit(0);
	}
	else
	{
		ft_putstr_fd(s_err, 2);
		exit(1);
	}
}

void	clear_thread_n_mutex(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	while (i < arg->nb)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&arg->mtx_write);
	pthread_mutex_destroy(&arg->mtx_meals);
	pthread_mutex_destroy(&arg->mtx_time);
	pthread_mutex_destroy(&arg->mtx_stop);
	free(philo);
}

int		show_must_go_on(t_philo *philo, t_arg *arg)
{
	pthread_mutex_lock(&(philo->a->mtx_stop));
	pthread_mutex_lock(&(philo->a->mtx_meals));
	if (arg->stop == one_died)
	{
		pthread_mutex_unlock(&(philo->a->mtx_meals));
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		return (one_died);
	}
	if (arg->stop == all_have_eaten)
	{
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		pthread_mutex_unlock(&(philo->a->mtx_meals));
		return (all_have_eaten);
	}
	pthread_mutex_unlock(&(philo->a->mtx_meals));
	pthread_mutex_unlock(&(philo->a->mtx_stop));
	return (0);
}

void	stop_show(t_philo *philo, t_arg *arg, int ret)
{
	clear_thread_n_mutex(philo, arg);
	if (ret == one_died)
		ft_exit("A philosopher died\n", no_error);
	if (ret == all_have_eaten)
		ft_exit("All philosophers have eaten\n", no_error);
	if (ret == 3)
		ft_exit("Error: Fail to create thread\n", error);
}

void	ctrl_thread(t_philo *philo, t_arg *arg)
{
	int	ret;

	ret = 0;
	while(!(ret = show_must_go_on(philo, arg)))
		usleep(1000);
	stop_show(philo, arg, ret);
}