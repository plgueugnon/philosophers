#include "philo.h"



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
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		size;

	size = ft_numlen(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	ft_fill_str(str, n, size);
	return (str);
}