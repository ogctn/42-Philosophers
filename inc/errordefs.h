/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errordefs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:55:01 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/23 12:45:58 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORDEFS_H
# define ERRORDEFS_H

# define TRUE 1
# define FALSE 0

# define TAKE_FORK " has taken a fork"
# define THINK " is thinking"
# define SLEEP " is sleeping"
# define EAT " is eating"
# define DIED " died"

typedef enum e_errors
{
	few_arguments,
	many_arguments,
	die_is_not_number,
	eat_is_not_number,
	sleep_is_not_number,
	must_eat_is_not_number,
	negative_number,
}	t_errors;

# define ERR_ARG_NUMBER "Please check number of the arguments!"
# define ERR_TOO_FEW "Too few arguments!"
# define ERR_TOO_MANY "Too many arguments!"
# define ERR_NEGATIVE "All arguments must be positive!"
# define ERR_DIE "Check {time_to_die}, parameter is not a number!"
# define ERR_EAT "Check {time_to_eat}, parameter is not a number!"
# define ERR_SLEEP "Check {time_to_sleep}, parameter is not a number!"
# define ERR_MUST_EAT "Check {max_number_of_eat}, parameter is not a number!"
# define ERR_NOT_A_NUMBER "All arguments must be numeric and positive!"
# define ERR_U0 "Usage:\n"
# define ERR_U1 "./philo [number_of_philos] [time_to_die] [time_to_sleep] "
# define ERR_U2 "[time_to_eat] [*optional: max_number_of_eat]\n"
# define ERR_U3 "./philo 5 300 100 100    ->(max_number_of_eat is not given)\n"
# define ERR_U4 "./philo 5 300 100 100 7  ->(max_number_of_eat is given)\n"
# define ERR_THREAD "Threading error!"
#endif
