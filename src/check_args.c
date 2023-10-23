/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:25:06 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/23 02:54:09 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	usage(int e)
{
	printf("---------------------------------------------------");
	printf("---------------------------------------------------\n");
	if (e == few_arguments)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_ARG_NUMBER, ERR_TOO_FEW);
	if (e == many_arguments)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_ARG_NUMBER, ERR_TOO_MANY);
	if (e == die_is_not_number)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_DIE, ERR_NOT_A_NUMBER);
	if (e == eat_is_not_number)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_EAT, ERR_NOT_A_NUMBER);
	if (e == sleep_is_not_number)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_SLEEP, ERR_NOT_A_NUMBER);
	if (e == must_eat_is_not_number)
		printf("\t\t\t%s\n\t\t\t\t%s\n", ERR_MUST_EAT, ERR_NOT_A_NUMBER);
	if (e == negative_number)
		printf("\t\t\t%s\n", ERR_NEGATIVE);
	printf("---------------------------------------------------");
	printf("---------------------------------------------------\n");
	printf("%s%s%s\t%s\t%s", ERR_U0, ERR_U1, ERR_U2, ERR_U3, ERR_U4);
	printf("---------------------------------------------------");
	printf("---------------------------------------------------\n");
}

static int	is_only_digits(char *nb)
{
	int	i;

	i = 0;
	if (!nb || !nb[0])
		return (0);
	while (nb[i] == '+')
		i++;
	while (nb[i])
	{
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	is_all_positive(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!av[i])
		return (0);
	while (av[i])
	{
		j = 0;
		while (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	printf("ac: %d son: %s is_o_d: %d\n", ac, av[4], is_only_digits(av[4]));
	if (ac < 5)
		return (usage(few_arguments), 1);
	if (ac > 6)
		return (usage(many_arguments), 1);
	if (!is_only_digits(av[1]))
		return (usage(die_is_not_number), 1);
	if (!is_only_digits(av[2]))
		return (usage(eat_is_not_number), 1);
	if (!is_only_digits(av[3]))
		return (usage(sleep_is_not_number), 1);
	if (ac == 6 && !is_only_digits(av[5]))
		return (usage(must_eat_is_not_number), 1);
	if (!is_all_positive(av))
		return (usage(negative_number), 1);
	return (0);
}
