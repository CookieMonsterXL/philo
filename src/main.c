/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 19:26:22 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/28 17:56:56 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	//destroy_mutex(&state);
	//pthread_mutex_destroy((*philo)->mutex_print);
	free(philo);
	//free(state.mutex_fork);
	return (0);
}
