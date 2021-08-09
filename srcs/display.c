#include "philo.h"

static char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		len1;
	int		len2;
	int		j;
	char	*dst;

	j = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	len = len1 + len2;
	dst = malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (0);
	dst = ft_strcpy(dst, (char *)s1);
	while (j < len2)
	{
		dst[len1 + j] = *s2;
		s2++;
		j++;
	}
	*(dst + (len)) = '\0';
	return (dst);
}

void	print_activity(t_philo *philo, char *status)
{
	char			*tmp;
	char			*tmp2;
	unsigned int	time;
	
	if (check_status(philo->a))
		return ;
	time = gettime() - philo->a->ms_start;
	tmp = ft_strjoin(ft_uitoa(time), " philo # ");
	tmp2 = ft_strjoin(tmp, ft_uitoa(philo->id)); // va y avoir une fuite ici a cause uitoa
	free(tmp);
	tmp = ft_strjoin(tmp2, " ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, status);
	write(1, tmp2, ft_strlen(tmp2));
	free(tmp);
	free(tmp2);
}