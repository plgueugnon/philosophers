#include "philo.h"

int	is_it_a_valid_number(char *s)
{
	int		i;
	long	r;

	i = 0;
	while(s[i])
	{
		if (ft_isdigit(s[i]))
			i++;
		else if (!ft_isdigit(s[i]))
			ft_exit("Error: Invalid argument\n", error);
	}
	r = ft_atol(&(*s));
	if (r > INT_MAX || r < 0)
		ft_exit("Error: Invalid argument\n", error);
	return (r);
}

void	get_values(char *argv, t_arg *arg, int argc)
{
	int	l;

	l = 0;
	arg->max_meals = -1;
	l = is_it_a_valid_number(&(*argv));
	if (argc == 1)
		arg->nb = l;
	if (argc == 2)
		arg->ms_die = l;
	if (argc == 3)
		arg->ms_eat = l;
	if (argc == 4)
		arg->ms_sleep = l;
	if (argc == 5)
		arg->max_meals = l;
}

void	check_arg_validity(t_arg *arg)
{
	if (arg->nb < 2 || !arg->ms_die || !arg->ms_eat || !arg->ms_sleep
		|| !arg->max_meals)
		ft_exit("Error: Invalid argument\n", error);
	arg->ms_start = gettime();
	// arg->nb_meals = 0;
	arg->stop = do_nothing;
	pthread_mutex_init(&arg->mtx_write, NULL);
}

void	parse_arg(int argc, char **argv, t_ptr *ptr)
{
	int i;
	t_arg	arg;

	i = 1;
	ptr->a = &arg;
	while (i < argc)
	{
		get_values(argv[i], &arg, i);
		i++;
	}
	check_arg_validity(&arg);
	printf("arg 1 %u\n", ptr->a->nb);
	printf("arg 2 %u\n", ptr->a->ms_die);
	printf("arg 3 %u\n", ptr->a->ms_eat);
	printf("arg 4 %u\n", ptr->a->ms_sleep);
	printf("arg 5 %d\n", ptr->a->max_meals);

	ft_exit("It s OK\n", no_error);
}


int	main(int argc, char **argv)
{
	t_ptr	ptr;
	t_philo	*philo;
	if (argc >= 5 && argc <= 6)
	{
		parse_arg(argc, argv, &ptr);
		philo = malloc(sizeof(t_philo *) * ptr.a->nb);
		if (!philo)
			ft_exit("Error: Malloc failed\n", error);
		init_philo(philo, &ptr);
		return (1);
	}
	ft_exit("Error: Invalid number of arg\n", error);
    return (0);
}