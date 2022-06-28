/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 19:26:22 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/28 18:33:52 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	mutex_free(t_state *state)
{
	int i;

	i = 0;
	while (i < state->number_of_philo)
	{
		free(state->mutex_fork[i]);
		i++;
	}
	free(state->mutex_fork);
	free(state->mutex_done_eating);
	free(state->mutex_print);
	free(state->mutex_someone_died);
	return (0);
}

static int all_free(t_philo **philo, t_state *state)
{
	int	i;
	
	i = 0;
	mutex_free(state);
	while (i < state->number_of_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
	return (0);
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
	init_philo_arr(philo, &state, argc);
	start_program_time(&state);
	start_thread(philo);
	wait_thread(philo);
	destroy_mutex(&state);
	all_free(philo, &state);
	return (0);
}
