#include "philo.h"

unsigned int	gettime(void)
{
	unsigned int	time;
	struct timeval ctime;

	time = 0;
	gettimeofday(&ctime, NULL);
	time = ctime.tv_sec * 1000 + ctime.tv_usec / 10;
	return (time);
}

void	init_philo(t_philo *philo, t_ptr *ptr)
{
	unsigned int	i;


	i = 0;
	while(i < ptr->a->nb)
	{
		philo[i].id = i + 1;
		philo[i].alive = 1;
		philo[i].ms_last_meal = ptr->a->ms_start;
		philo[i].nb_meals = 0;
		pthread_mutex_init(philo[i].right_fork, NULL);
		if (i == ptr->a->nb - 1)
			philo[i].left_fork = philo[0].right_fork;
		else
			philo[i].left_fork = philo[i + 1].right_fork;
		i++;
	}
}