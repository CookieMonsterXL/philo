/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:26:22 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/19 17:06:10 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "includes/philo.h"
#include "includes/libft/libft.h"

int	eat(t_philo **philo)
{
	printf("eat\n");
	usleep(5000);
	(*philo)->timer_1++;
	printf("Eat timer is= %d\n", (*philo)->timer_1);
	return (0);
}

void	*philo_thread_func(void *ptr)
{
	t_philo			**philo;

	printf("philo_thread_func\n");
	philo = (t_philo **)ptr;
	usleep(1000);
	pthread_mutex_lock(&(*philo)->state->mutex[(*philo)->philo_n - 1]);
	eat(philo);
	pthread_mutex_unlock(&(*philo)->state->mutex[(*philo)->philo_n - 1]);
	printf("Philo_n = %d I slept\n", (*philo)->philo_n);
	return (ptr);
}

void	start_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		//printf("START_THREAD: Philo_index = %d\n", state->philo_index);
		pthread_create(&(*philo)[i].tid, NULL, philo_thread_func, (void *)philo);
		i++;
	}
}

void make_philo_arr(t_philo **philo, t_state *state)
{
	int	i;

	i = 0;
	//state->philo_arr = malloc(sizeof(t_philo) * state->number_of_philo);
	while (i < state->number_of_philo)
	{
		init_philo(philo[i], i, state);
		pthread_mutex_init(state->mutex + i, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_state			state;

	(void) argc;
	//(void) argv;
	printf("argv[1] = %d\n", ft_atoi(argv[1]));
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_state(&state, argv);
	make_philo_arr(&philo, &state);
	printf("test\n");
	//philo_print(&state);
	start_thread(&philo);
	destroy_mutex(&state);
	free(philo);
	free(state.mutex);
	pthread_exit(NULL);
	return (0);
}