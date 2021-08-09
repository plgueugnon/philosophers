#include "philo.h"

void	clear_thread_n_mutex(t_philo *philo, t_arg *arg)
{
	unsigned int	i;

	i = 0;
	while (i < arg->nb)
	{
		// pthread_mutex_destroy(&philo[i].right_fork);
		pthread_join(philo[i].thread, NULL);
		// pthread_detach(philo[i].thread);
		i++;
	}
	i = 0;
	while (i < arg->nb)
	{
		pthread_mutex_destroy(&philo[i].right_fork);
		i++;
	}
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
		return (0);
	}
	if (arg->stop == all_have_eaten)
	{
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		pthread_mutex_unlock(&(philo->a->mtx_meals));
		return (0);
	}
	// if (arg->all_meals >= (unsigned int)arg->max_meals)
	// {
	// 	print_activity(philo, "maj status 2\n");
	// 	arg->stop = all_have_eaten;
	// 	// print_activity(philo, "all have eaten\n");
	// 	pthread_mutex_unlock(&(philo->a->mtx_meals));
	// 	pthread_mutex_unlock(&(philo->a->mtx_stop));
	// 	// pthread_mutex_lock(&(arg->mtx_write));
	// 	return (0);
	// }
	pthread_mutex_unlock(&(philo->a->mtx_meals));
	pthread_mutex_unlock(&(philo->a->mtx_stop));
	return (1);
}

void	stop_show(t_philo *philo, t_arg *arg)
{
	if (arg->stop == one_died)
	{
		clear_thread_n_mutex(philo, arg);
		// pthread_mutex_unlock(&(philo->a->mtx_write));
		pthread_mutex_destroy(&arg->mtx_write); // voir si pas besoin unlock avant
		pthread_mutex_destroy(&arg->mtx_meals);
		pthread_mutex_destroy(&arg->mtx_time);
		pthread_mutex_destroy(&arg->mtx_stop);
		// printf("A philosopher died\n");
		// return ;
		ft_exit("A philosopher died\n", no_error);
	}
	if (arg->stop == all_have_eaten)
	{
		clear_thread_n_mutex(philo, arg);
		// pthread_mutex_unlock(&(philo->a->mtx_write));
		pthread_mutex_destroy(&arg->mtx_write);
		pthread_mutex_destroy(&arg->mtx_meals);
		pthread_mutex_destroy(&arg->mtx_time);
		pthread_mutex_destroy(&arg->mtx_stop);
		// printf("ll philosophers have eaten\n");
		// return ;
		ft_exit("All philosophers have eaten\n", no_error);
	}
}

void	ctrl_thread(t_philo *philo, t_arg *arg)
{
	while(show_must_go_on(philo, arg))
		usleep(1000);
	stop_show(philo, arg);
	// while(!arg->stop)
	// {
	// 	pthread_mutex_lock(&(philo->a->mtx_stop));
	// 	if (arg->all_meals >= (unsigned int)arg->max_meals)
	// 	{
	// 		arg->stop = all_have_eaten;
	// 		pthread_mu1tex_lock(&(arg->mtx_write)); // a voir si necessaire
	// 	}
	// 	pthread_mutex_unlock(&(philo->a->mtx_stop));
	// 	usleep(1000); // tant que pas maj de statut => attend
	// }
// 	if (arg->stop == one_died)
// 	{
// 		clear_thread_n_mutex(philo, arg);
// 		// pthread_mutex_unlock(&(philo->a->mtx_write));
// 		pthread_mutex_destroy(&arg->mtx_write); // voir si pas besoin unlock avant
// 		pthread_mutex_destroy(&arg->mtx_meals);
// 		pthread_mutex_destroy(&arg->mtx_time);
// 		pthread_mutex_destroy(&arg->mtx_stop);
// 		// printf("A philosopher died\n");
// 		// return ;
// 		ft_exit("A philosopher died\n", no_error);
// 	}
// 	if (arg->stop == all_have_eaten)
// 	{
// 		clear_thread_n_mutex(philo, arg);
// 		// pthread_mutex_unlock(&(philo->a->mtx_write));
// 		pthread_mutex_destroy(&arg->mtx_write);
// 		pthread_mutex_destroy(&arg->mtx_meals);
// 		pthread_mutex_destroy(&arg->mtx_time);
// 		pthread_mutex_destroy(&arg->mtx_stop);
// 		// printf("ll philosophers have eaten\n");
// 		// return ;
// 		ft_exit("All philosophers have eaten\n", no_error);
// 	}
}