/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:12:37 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/07 02:05:02 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clear_before_exit(t_info info)
{
	int	i;

	i = 0;
	while (i < info.n_philo)
	{
		pthread_mutex_destroy(info.philo[i].fork_l);
		i++;
	}
	free(info.addr_forks);
	pthread_mutex_destroy(&info.m_print);
	pthread_mutex_destroy(&info.m_stop);
	pthread_mutex_destroy(&info.m_eat);
	pthread_mutex_destroy(&info.m_dead);
	free(info.philo);
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_info	info;
	int i = 0;

	if (check_args(ac, av))
		return (1);
	if (init_info(&info, ac, av))
		return (2);
	if (init_philo(&info))
		return (clear_before_exit(info), 3);
	pthread_t monitor;
	pthread_create(&monitor, 0, &check_death, &info);
	while (i < info.n_philo)
	{
		pthread_join(info.philo[i].thread, 0);
		i++;
	}
	pthread_join(monitor, 0);
	return (clear_before_exit(info), 0);
}
