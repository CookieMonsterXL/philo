/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 13:39:59 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->state->mutex_fork[philo->philo_n]))
		error_msg("Error: mutex_lock\n");
	if (pthread_mutex_lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]))
		error_msg("Error: mutex_lock\n");
	action_print(philo, " is eating\n");
	timer(philo->state->time_to_eat);
	if (pthread_mutex_unlock(philo->state->mutex_fork[philo->philo_n]))
		error_msg("Error: mutex_unlock\n");
	if (pthread_mutex_unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]))
		error_msg("Error: mutex_unlock\n");
	return (0);
}

int	p_sleep(t_philo *philo)
{
	action_print(philo, " is sleeping\n");
	timer(philo->state->time_to_sleep);
	return (0);
}
