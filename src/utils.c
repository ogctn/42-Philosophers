/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:33:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/23 18:00:57 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep_ms(int ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(ms / 4);
}

int	set_check_dead(t_philo *philo, int n)
{
	pthread_mutex_lock(&(philo->info->m_dead));
	if (n)
	{
		pthread_mutex_lock(&(philo->info->m_set_check));
		philo->info->stop = 1;
		pthread_mutex_unlock(&(philo->info->m_set_check));
	}
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&(philo->info->m_dead));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->m_dead));
	return (0);
}

void	print_stat(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&(philo->info->m_print));
	time = get_time() - philo->info->t_start;
	pthread_mutex_lock(&(philo->info->m_set_check));
	if (!philo->info->stop && time >= 0 && !set_check_dead(philo, 0))
		printf("%lld %d %s\n",
			get_time() - philo->info->t_start, philo->n, str);
	pthread_mutex_unlock(&(philo->info->m_set_check));
	pthread_mutex_unlock(&(philo->info->m_print));
}
