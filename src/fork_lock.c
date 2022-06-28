/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_lock_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 16:40:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/28 16:56:07 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	fork_lock_1(t_philo *philo)
{
	int checker;

	checker = 0;
	while(1)
	{
		lock(philo->state->mutex_fork[philo->philo_n]);
		if (philo->state->bool_fork[philo->philo_n] == true)
		{
			philo->state->bool_fork[philo->philo_n] = false;
			unlock(philo->state->mutex_fork[philo->philo_n]);
			break ;
		}
		unlock(philo->state->mutex_fork[philo->philo_n]);
		usleep(150);
		checker = check_die_timer(philo);
		if (checker != 0)
			break ;
	}
	return (checker);
}


int	fork_lock_2(t_philo *philo)
{
	int checker;

	checker = 0;
	while(1)
	{
		lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
		if (philo->state->bool_fork[(philo->philo_n + 1) % philo->state->number_of_philo] == true)
		{
			philo->state->bool_fork[(philo->philo_n + 1) % philo->state->number_of_philo] = false;
			unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
			break ;
		}
		unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
		usleep(200);
		checker = check_die_timer(philo);
		if (checker != 0)
			break ;
	}
	return (checker);
}

int fork_unlock_1(t_philo *philo)
{
	lock(philo->state->mutex_fork[philo->philo_n]);
	philo->state->bool_fork[philo->philo_n] = true;
	unlock(philo->state->mutex_fork[philo->philo_n]);
	return (0);
}

int fork_unlock_2(t_philo *philo)
{
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	philo->state->bool_fork[(philo->philo_n + 1) % philo->state->number_of_philo] = true;
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	return (0);
}
