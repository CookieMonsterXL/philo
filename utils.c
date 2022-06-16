/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:39:43 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/16 17:48:10 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "includes/philo.h"

void	init_state(t_state *state)
{
	state->number_of_philo = 5;
    state->number_of_forks = state->number_of_philo;
    state->time_to_die = 100;
    state->time_to_sleep = 100;
    state->time_to_eat = 100;
}

void	init_philo(t_philo *philo, int index)
{
	philo->philo_n = index + 1;
	philo->spoon = 1;
	philo->timer_1 = 0;
	philo->timer_2 = 0;
}

void	philo_print(t_state *state)
{
	int i;

	i = 0;
	while (i < state->number_of_philo)
	{
		printf("p_num %d\n", state->philo_arr[i].philo_n);
		i++;
	}
	
}