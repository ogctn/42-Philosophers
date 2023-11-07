/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:30:58 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/07 03:42:19 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_stop(t_info *info, int i)
{
	pthread_mutex_lock(&info->m_dead);
	info->stop = 1;
	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_unlock(info->philo[i].fork_l);
		pthread_mutex_unlock(info->philo[i].fork_r);
		i++;
	}
	pthread_mutex_unlock(&info->m_dead);
}

void	*check_death(void *p_info)
{
	t_info	*info;
	int		i;

	info = (t_info *)p_info;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->m_eat);
		if (info->philo[i].m_count == info->n_eat)
		{
			pthread_mutex_unlock(&info->m_eat);
			return (NULL);
		}
		if (get_time() - info->philo[i].last_eat > info->t_die)
		{
			pthread_mutex_unlock(&info->m_eat);
			print_status(&info->philo[i], "died");
			set_stop(info, i);
			return (NULL);
		}
		pthread_mutex_unlock(&info->m_eat);
		i++;
		i = i % info->n_philo;
	}
	return (NULL);
}

int	routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_eat = get_time();
	print_status(philo, "is eating");
	if (philo->info->n_eat != -1)
		philo->m_count++;
	if (philo->m_count == philo->info->n_eat)
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	ft_sleep_ms(philo->info->t_eat, philo->info);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	print_status(philo, "is sleeping");
	ft_sleep_ms(philo->info->t_sleep, philo->info);
	return (0);
}

void	*philo_life(void *a_philo)
{
	t_philo	*philo;

	philo = (t_philo *)a_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->info->m_dead);
		if (philo->info->stop)
		{
			pthread_mutex_unlock(&philo->info->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->m_dead);
		if (philo->n % 2 == 0)
			usleep(100);
		if (routine(philo) == 1)
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
