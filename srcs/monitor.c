/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 13:00:54 by pgueugno          #+#    #+#             */
/*   Updated: 2021/08/11 13:00:56 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *s_err, int err)
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

int	show_must_go_on(t_philo *philo, t_arg *arg, int *ret)
{
	pthread_mutex_lock(&(philo->a->mtx_meals));
	pthread_mutex_lock(&(philo->a->mtx_stop));
	if (arg->stop == one_died)
	{
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		pthread_mutex_unlock(&(philo->a->mtx_meals));
		*ret = one_died;
		return (one_died);
	}
	if (arg->stop == all_have_eaten)
	{
		pthread_mutex_unlock(&(philo->a->mtx_meals));
		pthread_mutex_unlock(&(philo->a->mtx_stop));
		*ret = all_have_eaten;
		return (all_have_eaten);
	}
	pthread_mutex_unlock(&(philo->a->mtx_stop));
	pthread_mutex_unlock(&(philo->a->mtx_meals));
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
	while (!(show_must_go_on(philo, arg, &ret)))
		usleep(1000);
	stop_show(philo, arg, ret);
}
