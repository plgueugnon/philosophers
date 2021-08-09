#include "philo.h"

static int	ft_numlen(int n)
{
	if (n < 0)
		n *= -1;
	if (n < 10)
		return (1);
	return (ft_numlen(n / 10) + 1);
}

static void	ft_fill_str(char *str, unsigned int n, int size)
{
	str[size] = '\0';
	size--;
	while (n >= 10)
	{
		str[size] = (n % 10) + 48;
		size--;
		n /= 10;
	}
	while (n < 10 && size >= 0)
	{
		str[size] = (n % 10) + 48;
		size--;
	}
	// if (s < 0)
	// 	str[0] = '-';
}

// static char	*ft_cpy_str(char *s, int start, int len)
// {
// 	char	*dst;
// 	int		i;

// 	i = 0;
// 	dst = malloc(sizeof(char) * (len + 1));
// 	if (dst == NULL)
// 		return (0);
// 	while (i < len)
// 	{
// 		dst[i] = s[start + i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	// int		s;
	int		size;
	// char	*s_intmin;

	// s_intmin = "-2147483648";
	// if (n < -2147483647)
	// 	return (ft_cpy_str(s_intmin, 0, 12));
	// if (n < 0)
	// 	s = -1;
	// else
	// 	s = 1;
	// if (s < 0)
	// 	n *= -1;
	size = ft_numlen(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	ft_fill_str(str, n, size);
	return (str);
}