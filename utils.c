/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:39:43 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/19 17:02:28 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "includes/philo.h"
#include "includes/libft/libft.h"

void	init_state(t_state *state, char **argv)
{
	state->number_of_philo = ft_atoi(argv[1]);
	state->number_of_forks = state->number_of_philo;
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->mutex = malloc(sizeof(pthread_mutex_t) * state->number_of_philo);
}

void	init_philo(t_philo *philo, int index, t_state *state)
{
	philo->philo_n = index + 1;
	philo->spoon = 1;
	philo->timer_1 = 0;
	philo->timer_2 = 0;
	// philo->state->mutex = state->mutex;
	philo->state = state;
}

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

int	destroy_mutex(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philo)
	{
		pthread_mutex_destroy(&state->mutex[i]);
		i++;
	}
	return (0);
}