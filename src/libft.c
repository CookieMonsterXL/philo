/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:34:30 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/12 11:05:33 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	atoi_h(long long num_l, int minplus)
{
	num_l *= minplus;
	if (num_l < INT_MIN || num_l > INT_MAX)
		return (0);
	return (num_l);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			num;
	long long	num_l;
	int			minplus;

	i = 0;
	num_l = 0;
	minplus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minplus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num_l *= 10;
		num_l += str[i] - 48;
		i++;
	}
	num = atoi_h(num_l, minplus);
	return (num);
}

int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\n' || c == '\t'
			|| c == '\v' || c == '\r' || c == '\f'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
