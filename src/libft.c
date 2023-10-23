/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:43:29 by ogcetin           #+#    #+#             */
/*   Updated: 2023/10/23 02:01:01 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi_positive(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	result = 0;
	while (is_space(str[i]) || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i++] - 48);
		else
			return (-1);
	}
	if (str[i - 1] == '+' || result > 2147483647)
		return (-1);
	return (result);
}
