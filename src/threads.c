/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:04:05 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/12 10:31:55 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	set_err(t_state *state)
{
	pthread_mutex_lock(state->mutex_someone_died);
	state->someone_died = 1;
	pthread_mutex_unlock(state->mutex_someone_died);
	return (0);
}

void	*philo_thread_func(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_n % 2 == 0)
		usleep(500);
	if (reset_die_timer(philo))
		return (NULL);
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

int	wait_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		if (pthread_join(philo[i]->tid, NULL))
		{
			error_msg("Error: Tread error.\n");
			set_err((*philo)->state);
			return (ERR);
		}
		i++;
	}
	return (0);
}

int	start_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		if (pthread_create(&philo[i]->tid, NULL,
				philo_thread_func, (void *)philo[i]))
		{
			error_msg("Error: Tread error.\n");
			set_err((*philo)->state);
			return (ERR);
		}	
		i++;
	}
	return (0);
}
