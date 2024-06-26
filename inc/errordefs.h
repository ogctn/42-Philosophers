/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errordefs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:55:01 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/07 03:36:20 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORDEFS_H
# define ERRORDEFS_H

typedef enum e_errors
{
	few_arguments,
	many_arguments,
	philo_number,
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
# define ERR_NO_OF_PH "Check {number_of_philos}!"
# define ERR_DIE "Check {time_to_die}!"
# define ERR_EAT "Check {time_to_eat}!"
# define ERR_SLEEP "Check {time_to_sleep}!"
# define ERR_MUST_EAT "Check {max_number_of_eat}!"
# define ERR_NOT_A_NUMBER "All arguments must be numeric and positive!"
# define ERR_U0 "Usage:\n"
# define ERR_U1 "./philo [number_of_philos] [time_to_die] [time_to_sleep] "
# define ERR_U2 "[time_to_eat] [*optional: max_number_of_eat]\n"
# define ERR_U3 "./philo 5 300 100 100    ->(max_number_of_eat is not given)\n"
# define ERR_U4 "./philo 5 300 100 100 7  ->(max_number_of_eat is given)\n"
# define ERR_THREAD "THREAD error!"
# define ERR_MALLOC "MALLOC error!"

#endif
