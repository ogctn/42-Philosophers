/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:12:37 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/23 18:10:24 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	before_exit(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->philo[i].fork_l);
		pthread_mutex_destroy(info->philo[i].fork_r);
		i++;
	}
	pthread_mutex_destroy(&info->m_print);
	pthread_mutex_destroy(&info->m_stop);
	pthread_mutex_destroy(&info->m_eat);
	pthread_mutex_destroy(&info->m_dead);
	free(info->philo);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (check_args(ac, av))
		return (1);
	if (init_info(&info, ac, av))
		return (2);
	if (do_philos(&info))
	{
		before_exit(&info);
		printf("#\t\t%s\t\t#\n", ERR_THREAD);
		return (3);
	}
	return (before_exit(&info), 0);
}
