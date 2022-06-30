/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:55 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/30 11:24:53 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*make_mutex(pthread_mutex_t *mutex, int *checker)
{
	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		*checker = MALLOC_ERR;
	if (pthread_mutex_init(mutex, NULL))
		*checker = LOCK_ERR;
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
	} //NEEDS TO BE PROTECTED
	pthread_mutex_destroy(state->mutex_print);
	pthread_mutex_destroy(state->mutex_someone_died);
	pthread_mutex_destroy(state->mutex_done_eating);
	return (0);
}
