/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 19:26:22 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/16 17:24:13 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "includes/philo.h"

void *philo_thread_func(void *ptr)
{
	t_philo *philo;
	
	printf("philo_thread_func\n");
	philo = (t_philo *)ptr;
	usleep(1000);
	printf("I slept, my ID is= %ld\n", philo->tid);
	return (ptr);
}

void	start_thread(t_state *state)
{
	int	i;

	i = 0;
	while (state->number_of_philo > i)
	{
		printf("start_thread\n");
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
	//int			i;
	//pthread_t	*philo_arr;

	(void) argc;
	(void) argv;
	//i = 0;
	init_state(&state);
	printf("main\n");
	make_philo_arr(&state);
	philo_print(&state);
	printf("main\n");
	start_thread(&state);
	printf("main\n");
    // while (state.number_of_philo > i)
    // {
    //     pthread_create(new_thread, NULL, philo_thread_func, &state);
    //     i++;
        
    // }
	pthread_exit(NULL);
	
}