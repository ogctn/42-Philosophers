/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:32:50 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/07 02:04:25 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_info(t_info *info, int ac, char **av)
{
	if (ac == 6)
		info->n_eat = ft_atoi_positive(av[5]);
	else
		info->n_eat = -1;
	info->n_philo = ft_atoi_positive(av[1]);
	if (info->n_eat == 0 || info->n_philo == 0)
		return (1);
	info->philo = malloc(sizeof(t_philo) * info->n_philo);
	if (!info->philo)
		return (printf("%s\n", ERR_MALLOC), -1);
	pthread_mutex_init(&info->m_print, 0);
	pthread_mutex_init(&info->m_stop, 0);
	pthread_mutex_init(&info->m_eat, 0);
	pthread_mutex_init(&info->m_dead, 0);
	info->t_die = ft_atoi_positive(av[2]);
	info->t_eat = ft_atoi_positive(av[3]);
	info->t_sleep = ft_atoi_positive(av[4]);
	if (av[5])
		info->n_eat = ft_atoi_positive(av[5]);
	else
		info->n_eat = -1;
	info->philo_eat = 0;
	info->stop = 0;
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	info->addr_forks = forks;
	info->t_start = get_time();
	i = -1;
	while (++i < info->n_philo)
	{
		info->philo[i].n = i + 1;
		info->philo[i].m_count = 0;
		info->philo[i].last_eat = info->t_start;
		info->philo[i].info = info;
		info->philo[i].fork_l = &forks[i];
		info->philo[i].fork_r = &forks[(i + 1) % info->n_philo];
		pthread_mutex_init(&forks[i], 0);
		if (pthread_create(&info->philo[i].thread,
				0, &philo_life, &info->philo[i]))
			return (printf("%s\n", ERR_THREAD), -1);
	}
	return (0);
}
