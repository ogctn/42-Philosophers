/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:32:50 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/24 17:30:11 by ogcetin          ###   ########.fr       */
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
	pthread_mutex_init(&info->m_condition, 0);
	info->t_die = ft_atoi_positive(av[2]);
	info->t_eat = ft_atoi_positive(av[3]);
	info->t_sleep = ft_atoi_positive(av[4]);
	info->philo_eat = 0;
	info->stop = 0;
	return (0);
}

int	do_philos(t_info *info)
{
	int	i;

	info->t_start = get_time();
	i = -1;
	while (++i < info->n_philo)
	{
		info->philo[i].n = i + 1;
		info->philo[i].m_count = 0;
		info->philo[i].last_eat = 0;
		info->philo[i].info = info;
		pthread_mutex_init(&info->philo[i].fork_l, 0);
		if (i != info->n_philo - 1)
			info->philo[i].fork_r = &info->philo[i + 1].fork_l;
		else
			info->philo[i].fork_r = &info->philo[0].fork_l;
		if (pthread_create(&info->philo[i].thread,
				0, &philo_life, &info->philo[i]))
			return (printf("%s\n", ERR_THREAD), -1);
	}
	i = -1;
	while (++i < info->n_philo)
		if (pthread_join(info->philo[i].thread, 0))
			return (printf("%s\n", ERR_THREAD), -2);
	return (0);
}
