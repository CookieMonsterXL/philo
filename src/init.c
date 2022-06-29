/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:23:39 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/29 18:21:19 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_state2(t_state *state, char **argv, int argc)
{
	int	checker;

	checker = 0;
	if (argc == 6)
	{
		state->meals_per_philo = ft_atoi(argv[5]);
		state->total_meals_still_needed = state->meals_per_philo
			* state->number_of_philo;
	}
	else
		state->total_meals_still_needed = -1;
	state->mutex_print = make_mutex(state->mutex_print, &checker);
	if (checker != 0)
		return (checker);
	state->mutex_someone_died = make_mutex(state->mutex_someone_died, &checker);
	if (checker != 0)
		return (checker);
	state->mutex_done_eating = make_mutex(state->mutex_done_eating, &checker);
	if (checker != 0)
		return (checker);
	return (0);
}

int	init_state(t_philo **philo, t_state *state, char **argv, int argc)
{
	state->number_of_philo = ft_atoi(argv[1]);
	state->number_of_forks = state->number_of_philo;
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->mutex_fork = malloc(sizeof(pthread_mutex_t *)
			* state->number_of_philo);
	if (state->mutex_fork == NULL)
		return (MALLOC_ERR);
	state->bool_fork = malloc(sizeof(bool) * state->number_of_philo);
	if (state->bool_fork == NULL)
		return (MALLOC_ERR);
	init_bool(state);
	state->someone_died = 0;
	state->done_eating = 0;
	if (init_state2(state, argv, argc) != 0)
		return (ERR);
	if (init_philo_arr(philo, state, argc))
		return (MALLOC_ERR);
	return (0);
}

int	init_bool(t_state *state)
{
	int	i;

	i = 0;
	while (state->number_of_philo > i)
	{
		state->bool_fork[i] = true;
		i++;
	}
	return (0);
}

int	init_philo(t_philo **philo, int index, t_state *state, int argc)
{
	int	checker;

	checker = 0;
	*philo = malloc(sizeof(t_philo));
	if (*philo == NULL)
		return (MALLOC_ERR);
	(*philo)->philo_n = index;
	(*philo)->is_dead = 0;
	(*philo)->state = state;
	(*philo)->state->mutex_fork[index] = malloc(sizeof(pthread_mutex_t));
	if ((*philo)->state->mutex_fork[index] == NULL)
		return (MALLOC_ERR);
	(*philo)->state->bool_fork[index] = true;
	if (argc == 6)
		(*philo)->meal_count = 0;
	if (argc == 5)
		(*philo)->meal_count = -1;
	return (0);
}

int	init_philo_arr(t_philo **philo, t_state *state, int argc)
{
	int	i;

	i = 0;
	while (i < state->number_of_philo)
	{
		if (init_philo(&philo[i], i, state, argc))
			return (MALLOC_ERR);
		if (pthread_mutex_init(state->mutex_fork[i], NULL))
			return (LOCK_ERR);
		i++;
	}
	return (0);
}
