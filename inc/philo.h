/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:09:11 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/06 19:59:11 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>
# include "./errordefs.h"

typedef struct s_philo
{
	int				n;
	int				m_count;
	int				is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct s_info	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}		t_philo;

typedef struct s_info
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				philo_eat;
	int				stop;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}		t_info;

int			ft_atoi_positive(char *str);
int			check_args(int ac, char **av);

long long	get_time(void);
void		ft_sleep_ms(int ms, t_info *info);
void		print_status(t_philo *philo, char *str);

int			init_info(t_info *info, int ac, char **av);
int			init_philo(t_info *info);

void		*philo_life(void *a_philo);
void		clear_before_exit(t_info info);
void	*check_death(void *p_info);

#endif
