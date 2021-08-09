#include "philo.h"

// void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&(philo->a->mtx_write));
// }

void	philo_take_forks(t_philo *philo)
{
	// if (!show_must_go_on(philo, philo->a))
	// 	return ;
    pthread_mutex_lock(&philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(philo->a->mtx_write)); // a voir si obli
	print_activity(philo, "has taken a fork\n");
	print_activity(philo, "has taken a fork\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
}

void	philo_eat(t_philo *philo)
{
	// if (!show_must_go_on(philo, philo->a))
	// 	return ;
	pthread_mutex_lock(&(philo->a->mtx_write)); // tester si marche sans mais a priori non
	print_activity(philo, "is eating\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
	pthread_mutex_lock(&(philo->a->mtx_time)); // mutex qui fait echouer 4 410 200 200
	philo->ms_last_meal = gettime();
	pthread_mutex_unlock(&(philo->a->mtx_time));
	// pthread_mutex_unlock(&(philo->a->mtx_write));
	// philo->ms_last_meal = gettime();
	// ms_sleep(philo->a->ms_eat);
	usleep(philo->a->ms_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	 // a voir si pas a inverser
}

void	philo_sleep(t_philo *philo)
{
	// if (!show_must_go_on(philo, philo->a))
	// 	return ;
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "is sleeping\n");
	pthread_mutex_unlock(&(philo->a->mtx_write)); // je le mets avant usleep pour pas bloquer inutilement mtx
	// ms_sleep(philo->a->ms_sleep);
	usleep(philo->a->ms_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	// if (!show_must_go_on(philo, philo->a))
	// 	return ;
	pthread_mutex_lock(&(philo->a->mtx_write));
	print_activity(philo, "is thinking\n");
	pthread_mutex_unlock(&(philo->a->mtx_write));
}