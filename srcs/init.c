#include "philo.h"

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

// void		ms_sleep(unsigned int ms_time)
// {
// 	unsigned int start_time;

// 	start_time = gettime();
// 	while (gettime() - start_time < ms_time)
// 		usleep(ms_time / 10 );
// }

void	init_philo(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	// printf("check %u\n", arg->nb);
	while(i < arg->nb)
	{
		// printf("check philo %p\n", &philo[i].id);
		// philo[i] = NULL;
		philo[i].id = i + 1;
		// printf("id = %u\n", philo[i].id);
		philo[i].alive = 1;
		// printf("id is alive = %u\n", philo[i].alive);
		philo[i].ms_last_meal = arg->ms_start;
		philo[i].a = arg;
		// printf("id last meal = %u\n", philo[i].ms_last_meal);
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