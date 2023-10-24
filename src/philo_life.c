/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:30:58 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/24 17:02:41 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*check_death(void *a_philo)
{
	t_philo	*philo;

	philo = (t_philo *)a_philo;
	ft_sleep_ms(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!manage_death_condition(philo, 0)
		&& get_time() - philo->last_eat >= philo->info->t_die)
	{
		print_stat(philo, DIED);
		manage_death_condition(philo, 1);
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (0);
}

void	eat(t_philo *philo)
{
	print_stat(philo, EAT);
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_eat = get_time();
	philo->m_count++;
	pthread_mutex_unlock(&philo->info->m_eat);
	ft_sleep_ms(philo->info->t_eat);
	pthread_mutex_unlock(&(philo->fork_l));
	pthread_mutex_unlock(philo->fork_r);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print_stat(philo, TAKE_FORK);
	if (philo->info->n_philo == 1)
	{
		ft_sleep_ms(philo->info->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	print_stat(philo, TAKE_FORK);
	eat(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_stat(philo, SLEEP);
	ft_sleep_ms(philo->info->t_sleep);
	print_stat(philo, THINK);
}

void	*philo_life(void *a_philo)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)a_philo;
	if (philo->n % 2 == 0)
		ft_sleep_ms(philo->info->t_eat / 10);
	while (!manage_death_condition(philo, 0))
	{
		pthread_create(&t, 0, &check_death, a_philo);
		take_fork(philo);
		pthread_detach(t);
		if (philo->m_count == philo->info->n_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				manage_death_condition(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (0);
		}
		philo_sleep(philo);
	}
	return (0);
}
