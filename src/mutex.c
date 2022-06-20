/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:55 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 14:25:51 by tbouma           ###   ########.fr       */
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
