#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
    	pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "has taken a fork\n");
	print_activity(philo, "has taken a fork\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "is eating\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
	pthread_mutex_lock(&(philo->a->mtx_time));
	philo->ms_last_meal = gettime();
	pthread_mutex_unlock(&(philo->a->mtx_time));
	usleep(philo->a->ms_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "is sleeping\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
	usleep(philo->a->ms_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "is thinking\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
}