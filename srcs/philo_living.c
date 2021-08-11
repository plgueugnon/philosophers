#include "philo.h"

void	*godess_of_death(void *value)
{
	t_philo *philo;

	philo = (t_philo *)value;
	if (philo->a->max_meals != -1 && philo->a->ms_die > (philo->a->nb * 100))
		usleep(philo->a->ms_die + 1 * 1000);
	else
		usleep(philo->a->ms_die * 1000);
	pthread_mutex_lock(&(philo->a->mtx_time));
	if (philo->alive && !check_status2(philo, philo->a) &&
		gettime() - philo->ms_last_meal > philo->ms_die)
	{
		pthread_mutex_unlock(&(philo->a->mtx_time));
		pthread_mutex_lock(&(philo->a->mtx_write));
		print_activity(philo, "died\n");
		pthread_mutex_lock(&(philo->a->mtx_stop));
		philo->a->stop = one_died;
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		pthread_mutex_unlock(&(philo->a->mtx_write));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->a->mtx_time));
	return (NULL);
}

void	increment_total_meals(t_philo *philo, t_arg *arg)
{
	pthread_mutex_lock(&(philo->a->mtx_meals));
	arg->all_meals++;
	pthread_mutex_unlock(&(philo->a->mtx_meals));
}

void	check_all_meals_counter(t_philo *philo, t_arg *arg)
{
	pthread_mutex_lock(&(philo->a->mtx_meals));
	if (arg->all_meals >= arg->nb)
	{
		pthread_mutex_lock(&(philo->a->mtx_stop));
		arg->stop = all_have_eaten;
		pthread_mutex_unlock(&(philo->a->mtx_stop));
	}
	pthread_mutex_unlock(&(philo->a->mtx_meals));
}

void	*chilling_like_a_philo(void *value)
{
	t_philo		*philo;
	t_arg		*arg;
	pthread_t	death;

	philo = (t_philo *)value;
	arg = philo->a;
	while (!check_status(arg))
	{
		if (pthread_create(&death, NULL, godess_of_death, philo))
			stop_show(philo, arg, 3);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		pthread_detach(death);
		if (arg->max_meals != -1 && (int)++philo->nb_meals >= arg->max_meals)
		{
			increment_total_meals(philo, arg);
			break ;
		}
	}	
	pthread_detach(death);
	check_all_meals_counter(philo, arg);
	return (NULL);
}

void	start_philo(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	while (i < arg->nb)
	{
		if (pthread_create(&(philo[i].thread), NULL,
			chilling_like_a_philo, &(philo[i])))
			stop_show(philo, arg, 3);
		usleep(10);
		i++;
	}
}