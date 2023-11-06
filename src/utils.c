/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:33:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/06 20:14:13 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep_ms(int ms, t_info *info)
{
	long long	start;

	start = get_time();
	while ((get_time() - start < ms))
	{
		pthread_mutex_lock(&(info->m_dead));
		if (info->stop)
		{
			pthread_mutex_unlock(&(info->m_dead));
			return ;
		}
		pthread_mutex_unlock(&(info->m_dead));
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&(philo->info->m_print));
	time = get_time() - philo->info->t_start;
	pthread_mutex_lock(&(philo->info->m_dead));
	if (!philo->info->stop && time >= 0)
	{
		printf("%lld %d %s\n", \
			get_time() - philo->info->t_start, philo->n, str);
	}
	pthread_mutex_unlock(&(philo->info->m_dead));
	pthread_mutex_unlock(&(philo->info->m_print));
}
