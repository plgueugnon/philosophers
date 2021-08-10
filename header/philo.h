#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include "struct.h"

int				ft_numlen(int n);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
long			ft_atol(const char *str);
int				ft_isdigit(int c);

void			print_activity(t_philo *philo, char *status);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_uitoa(unsigned int n);

int				check_status(t_arg *arg);
int				check_status2(t_philo *philo, t_arg *arg);
void			init_philo(t_philo *philo, t_arg *arg);
unsigned int	gettime(void);

void			start_philo(t_philo *philo, t_arg *arg);

void			philo_take_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

void			ctrl_thread(t_philo *philo, t_arg *arg);
void			stop_show(t_philo *philo, t_arg *arg, int ret);
void    		ft_exit(char *s_err, int err);

#endif