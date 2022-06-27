/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:26:22 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/27 12:22:23 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	checker_action(t_philo *philo, int checker)
{
	if (checker == SELF_DIE)
	{
		checker = die(philo);
		return (checker);
	}
	if (checker == OTHER_DIE)
		return (checker);
	if (checker == TIME_ERR)
		return (checker); // checken
	return (0);
}

void	*philo_thread_func(void *ptr)
{
	//int				checker;
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_n % 2 == 0)
		usleep(200);
	reset_die_timer(philo);
	while (1)
	{
		if (check_other_dead(philo) == OTHER_DIE)
			return (NULL);
		if (check_die_timer(philo) != 0)
			return (NULL);
		if (eat(philo) != 0)
			return (NULL);
		if (p_sleep(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

void	wait_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		pthread_join(philo[i]->tid, NULL);
		i++;
	}
}

void	start_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		pthread_create(&philo[i]->tid, NULL, philo_thread_func, (void *)philo[i]);
		i++;
	}
}

void	make_philo_arr(t_philo **philo, t_state *state)
{
	int	i;
	//pthread_mutex_t	*mutex_print;

	i = 0;
	state->mutex_print = make_mutex(state->mutex_print);
	state->mutex_die_print = make_mutex(state->mutex_die_print);
	state->mutex_someone_died = make_mutex(state->mutex_someone_died);
	while (i < state->number_of_philo)
	{
		init_philo(&philo[i], i, state);
		pthread_mutex_init(state->mutex_fork[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	t_state			state;

	(void) argc;
	philo = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	init_state(&state, argv);
	make_philo_arr(philo, &state);
	//philo_print(philo);
	start_program_time(&state);
	start_thread(philo);
	wait_thread(philo);
	//destroy_mutex(&state);
	//pthread_mutex_destroy((*philo)->mutex_print);
	//free(philo);
	//free(state.mutex_fork);
	//pthread_exit(NULL);
	return (0);
}
