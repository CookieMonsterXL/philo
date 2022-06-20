/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:55 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 17:03:34 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*make_print_mutex(void)
{
	pthread_mutex_t	*mutex_print;

	mutex_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_print, NULL);
	return (mutex_print);
}

pthread_mutex_t	*make_dead_mutex(void)
{
	pthread_mutex_t	*mutex_dead;

	mutex_dead = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_dead, NULL);
	return (mutex_dead);
}

int	destroy_mutex(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philo)
	{
		pthread_mutex_destroy(state->mutex_fork[i]);
		i++;
	}
	return (0);
}

void	lock(pthread_mutex_t *key)
{
	int	error;

	error = pthread_mutex_lock(key);
	if (error == 0)
		return ;
	else if (error == EINVAL)
		error_msg("Error mutex lock: The value specified by mutex is invalid.\n");
	else if (error == EDEADLK)
		error_msg("Error mutex lock: A deadlock would occur if the thread blocked waiting for mutex.\n");
}

void	unlock(pthread_mutex_t *key)
{
	int	error;
	
	error = pthread_mutex_unlock(key);
	if (error == 0)
		return ;
	else if (error == EINVAL)
		error_msg("Error mutex unlock: The value specified by mutex is invalid.\n");
	else if (error == EPERM)
		error_msg("Error mutex unlock: The current thread does not hold a lock on mutex.\n");
}
