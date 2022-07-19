/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:22:29 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/19 14:43:23 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_input3(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				error_msg("Characters other then digits in arguments.\n");
				return (2);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_input2(int argc, char **argv)
{
	if (ft_atoi(argv[3]) < 1 && ft_atoi(argv[3]) < 10000)
	{
		error_msg("Time to EAT wrong value.\n");
		return (2);
	}
	if (ft_atoi(argv[4]) < 1 && ft_atoi(argv[4]) < 10000)
	{
		error_msg("Time to SLEEP wrong value.\n");
		return (2);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 1 && ft_atoi(argv[5]) < 100000)
		{
			error_msg("Amount of meals wrong value.\n");
			return (2);
		}
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		error_msg("Wrong number of arguments\n");
		return (2);
	}
	if (ft_atoi(argv[1]) < 1 && ft_atoi(argv[1]) < 10000)
	{
		error_msg("To few or to many Philosophrs\n");
		return (2);
	}
	if (ft_atoi(argv[2]) < 1 && ft_atoi(argv[2]) < 10000)
	{
		error_msg("Time to DIE wrong value.\n");
		return (2);
	}
	if (check_input2(argc, argv))
		return (2);
	if (check_input3(argc, argv))
		return (2);
	return (0);
}
