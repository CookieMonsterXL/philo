/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 19:26:22 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/27 19:48:53 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*philo_thread_func(void *ptr)
{
	//int				checker;
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_n % 2 == 0)
		usleep(100);
	reset_die_timer(philo);
	while (1)
	{
		if (check_other_dead(philo) == OTHER_DIE)
			return (NULL);
		if (check_done_eating(philo) == 1)
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

	if ((*philo)->state->number_of_philo == 1)
	{
		
	}
	while ((*philo)->state->number_of_philo > i)
	{
		pthread_create(&philo[i]->tid, NULL, philo_thread_func, (void *)philo[i]);
		i++;
	}
}

void	make_philo_arr(t_philo **philo, t_state *state, int argc)
{
	int	i;

	i = 0;
	state->mutex_print = make_mutex(state->mutex_print);
	state->mutex_die_print = make_mutex(state->mutex_die_print);
	state->mutex_someone_died = make_mutex(state->mutex_someone_died);
	state->mutex_done_eating = make_mutex(state->mutex_done_eating);
	while (i < state->number_of_philo)
	{
		init_philo(&philo[i], i, state, argc);
		pthread_mutex_init(state->mutex_fork[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	t_state			state;

	if (argc < 5 || argc > 6)
	{
		error_msg("Wrong number of arguments\n");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1 && ft_atoi(argv[1]) < 10000)
	{
		error_msg("To few or to many Philosophrs\n");
		return (2);
	}
	philo = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (philo == NULL)
		return (3);
	init_state(&state, argv, argc);
	make_philo_arr(philo, &state, argc);
	start_program_time(&state);
	start_thread(philo);
	wait_thread(philo);
	//destroy_mutex(&state);
	//pthread_mutex_destroy((*philo)->mutex_print);
	free(philo);
	//free(state.mutex_fork);
	return (0);
}
