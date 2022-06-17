/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:26:22 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/17 16:29:18 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "includes/philo.h"

void	*philo_thread_func(void *ptr)
{
	t_philo	*philo;

	printf("philo_thread_func\n");
	philo = (t_philo *)ptr;
	usleep(1000);
	printf("Philo_n = %d I slept, my ID is= %ld\n", philo->philo_n, philo->tid);
	return (ptr);
}

void	start_thread(t_state *state)
{
	int	i;

	i = 0;
	while (state->number_of_philo > i)
	{
		pthread_create(&state->philo_arr[i].tid, NULL, philo_thread_func, (void *)&state->philo_arr[i]);
		i++;
	}
}

void make_philo_arr(t_state *state)
{
	int i;

	i = 0;
	state->philo_arr = malloc(sizeof(t_philo) * state->number_of_philo);

	while (i < state->number_of_philo)
	{
		init_philo(&state->philo_arr[i], i);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_state		state;

	(void) argc;
	(void) argv;
	init_state(&state);
	make_philo_arr(&state);
	//philo_print(&state);
	start_thread(&state);
	pthread_exit(NULL);
	return (0);
}