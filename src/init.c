/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 14:23:39 by tbouma        #+#    #+#                 */
/*   Updated: 2022/06/28 17:46:17 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_state(t_state *state, char **argv, int argc)
{
	state->number_of_philo = ft_atoi(argv[1]);
	state->number_of_forks = state->number_of_philo;
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->mutex_fork = malloc(sizeof(pthread_mutex_t *) * state->number_of_philo);
	if (state->mutex_fork == NULL)
		error_msg("Error: Malloc\n");
	state->bool_fork = malloc(sizeof(bool) * state->number_of_philo);
	if (state->bool_fork == NULL)
		error_msg("Error: Malloc\n");
	init_bool(state);
	state->someone_died = 0;
	state->done_eating = 0;
	if (argc == 6)
	{
		state->meals_per_philo = ft_atoi(argv[5]);
		state->total_meals_still_needed = state->meals_per_philo * state->number_of_philo;
	}
	else
		state->total_meals_still_needed = -1;

	state->mutex_print = make_mutex(state->mutex_print);
	state->mutex_someone_died = make_mutex(state->mutex_someone_died);
	state->mutex_done_eating = make_mutex(state->mutex_done_eating);
}

int init_bool(t_state *state)
{
	int i;

	i = 0;
	while(state->number_of_philo > i)
	{
		state->bool_fork[i] = true;
		i++;	
	}
	return (0);
}

void	init_philo(t_philo **philo, int index, t_state *state, int argc)
{
	*philo = malloc(sizeof(t_philo));
	(*philo)->philo_n = index;
	(*philo)->is_dead = 0;
	(*philo)->state = state;
	(*philo)->state->mutex_fork[index] = malloc(sizeof(pthread_mutex_t));
	(*philo)->state->bool_fork[index] = true;
	if (argc == 6)
		(*philo)->meal_count = 0;
	if (argc == 5)
		(*philo)->meal_count = -1;
}

void	init_philo_arr(t_philo **philo, t_state *state, int argc)
{
	int	i;

	i = 0;
	while (i < state->number_of_philo)
	{
		init_philo(&philo[i], i, state, argc);
		pthread_mutex_init(state->mutex_fork[i], NULL);
		i++;
	}
}