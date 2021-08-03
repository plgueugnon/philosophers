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