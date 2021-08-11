/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 13:05:14 by pgueugno          #+#    #+#             */
/*   Updated: 2021/08/11 13:05:16 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_numlen(int n)
{
	if (n < 0)
		n *= -1;
	if (n < 10)
		return (1);
	return (ft_numlen(n / 10) + 1);
}

size_t	ft_strlen(const char *s)
{
	if (*s == '\0')
		return (0);
	return (ft_strlen(s + 1) + 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long	ft_atol(const char *str)
{
	long	s;
	long	r;

	s = 1;
	r = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '-')
	{
		s *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		r = r * 10 + *str - 48;
		str++;
	}
	return (r * s);
}
