/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:30:58 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/07 02:35:14 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_is_full_eat(t_info *info, int i)
{
	pthread_mutex_lock(&info->m_eat);
	if (info->philo[i].m_count == info->n_eat)
	{
		pthread_mutex_unlock(&info->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&info->m_eat);
	return (0);
}
void	*check_death(void *p_info)
{
	t_info	*info;
	int		i;
	
	info = (t_info *)p_info;
	i = 0;
	while (1)
	{
		if (check_is_full_eat(info, i))
			return (NULL);
		if (get_time() - info->philo[i].last_eat > info->t_die)
		{
			print_status(&info->philo[i], "died");
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
			return (NULL);
		}
		pthread_mutex_unlock(&info->m_eat);
		i++;
		if (i == info->n_philo)
			i = 0;	
	}
	return (NULL);
}


int 	routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_eat = get_time();
	print_status(philo, "is eating");
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
	return 0;
}

void	*philo_life(void *a_philo)
{
	t_philo *philo;

	philo = (t_philo *)a_philo;
	if (philo->info->n_philo % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->info->m_dead);
		if (philo->info->stop)
		{
			pthread_mutex_unlock(&philo->info->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->m_dead);
		if (routine(philo) == 1)
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
