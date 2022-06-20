/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:15:22 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 14:16:10 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_print(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->state->number_of_philo)
	{
		printf("p_num %d\n", philo[i]->philo_n);
		i++;
	}
}
