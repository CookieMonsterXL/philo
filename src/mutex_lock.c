/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_lock.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 14:24:55 by tbouma        #+#    #+#                 */
/*   Updated: 2022/06/28 18:22:03 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*make_mutex(pthread_mutex_t *mutex)
{
	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	return (mutex);
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
	pthread_mutex_destroy(state->mutex_print);
	pthread_mutex_destroy(state->mutex_someone_died);
	pthread_mutex_destroy(state->mutex_done_eating);
	return (0);
}

int	lock(pthread_mutex_t *key)
{
	int	error;

	error = pthread_mutex_lock(key);
	if (error == 0)
		return (0);
	else if (error == EINVAL)
	{
		error_msg("Error mutex lock: The value specified by mutex is invalid.\n");
		return (EINVAL);
	}
	else if (error == EDEADLK)
	{
		error_msg("Error mutex lock: A deadlock would occur if the thread blocked waiting for mutex.\n");
		return(EDEADLK);
	}
	return (0);
}

int	unlock(pthread_mutex_t *key)
{
	int	error;
	
	error = pthread_mutex_unlock(key);
	if (error == 0)
		return (0);
	else if (error == EINVAL)
	{
		error_msg("Error mutex unlock: The value specified by mutex is invalid.\n");
		return (EINVAL);
	}
	else if (error == EPERM)
	{
		error_msg("Error mutex unlock: The current thread does not hold a lock on mutex.\n");
		return (EPERM);
	}
	return (0);
}
