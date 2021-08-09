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

void	*godess_of_death(void *value)
{
	t_philo *philo;
	// unsigned int	time;

	philo = (t_philo *)value;
	// 
	// time = gettime();
	// ms_sleep(philo->a->ms_die * 1000 + 1); // a tester
	usleep(philo->a->ms_die + 1 * 1000);
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
		// philo->alive = 0;
		// stop_show(philo, philo->a);
		pthread_mutex_unlock(&(philo->a->mtx_write));
	}
	pthread_mutex_unlock(&(philo->a->mtx_time));
	// usleep(philo->a->ms_die * 1000); // a tester
	return (NULL);
}

void	*chilling_like_a_philo(void *value)
{
	t_philo		*philo;
	t_arg		*arg;
	pthread_t	death;

	philo = (t_philo *)value;
	arg = philo->a;
	// printf("check arg %p\n", philo->a);
	// if (philo->id % 2 == 0)
	// 	usleep(10);
	while (!check_status(arg) /*&& philo->alive*/) //&& philo->alive
	// while (!arg->stop && philo->alive) 
	{
		if (pthread_create(&death, NULL, godess_of_death, philo))
			ft_exit("Error: Fail to create thread\n", error); // pas propre
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		pthread_detach(death); // deplacé voir si pas mieux
		// pthread_mutex_lock(&(philo->a->mtx_meals));
		if (arg->max_meals != -1 && (int)++philo->nb_meals >= arg->max_meals)
		{
			// printf("check nb meals %u\n", philo->nb_meals);
			pthread_mutex_lock(&(philo->a->mtx_meals));
			// print_activity(philo, "increase meal eaten\n");
			arg->all_meals++; // a voir si pas besoin proteger avec mtx
			// printf("%u\n", arg->all_meals);
			pthread_mutex_unlock(&(philo->a->mtx_meals));
			// if (arg->all_meals >= (unsigned int)arg->max_meals)
			// {
				// print_activity(philo, "all have eaten\n"); //debug
			pthread_detach(death);
			// 	arg->stop = all_have_eaten;
				// return NULL;
			// }
			// philo->alive = 0; // a priori pas utile ?
			break ;
			// return (NULL);
		}
		// pthread_mutex_unlock(&(philo->a->mtx_meals));
		
		// if (!arg->stop)
		// 	break ;
	}
	// pthread_mutex_unlock(&(philo->a->mtx_meals));
	// pthread_mutex_lock(&(philo->a->mtx_stop));
	
	pthread_detach(death);
	pthread_mutex_lock(&(philo->a->mtx_meals));
	if (arg->all_meals >= arg->nb)
	{
		// print_activity(philo, "maj status\n"); 
		// char *str = ft_uitoa(arg->all_meals);
		// char *tmp = ft_strjoin(str, "\n");
		// write(1, tmp, ft_strlen(tmp));
		// printf("%u\n", arg->all_meals);
		pthread_mutex_lock(&(philo->a->mtx_stop));
		arg->stop = all_have_eaten;
		pthread_mutex_unlock(&(philo->a->mtx_stop));
	}
	pthread_mutex_unlock(&(philo->a->mtx_meals));
	
	// print_activity(philo, "sortie du thread\n"); 
	// philo->alive = 0; //permet de couper le check death
	return (NULL);
}

void	start_philo(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	// arg->ms_start = gettime();
	while (i < arg->nb)
	{
		if (pthread_create(&(philo[i].thread), NULL,
			chilling_like_a_philo, &(philo[i])))
			ft_exit("Error: Fail to create thread\n", error); // pas propre
		usleep(10); // a tester
		i++;
	}
}