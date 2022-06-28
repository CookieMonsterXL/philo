/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_set_var.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 16:57:14 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/28 17:00:51 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	check_die_timer(t_philo *philo)
{
	int checker;

	checker = 0;
	if (get_time(&philo->current_die_timeval, &philo->current_die_timer))
		return (TIME_ERR);
	if (((philo->current_die_timer - philo->start_die_timer)) > philo->state->time_to_die * 1000)
	{
		checker = die(philo);
		return (checker);
	}
	else
		return (checker);
}

int	check_other_dead(t_philo *philo)
{
	int checker;

	checker = NOT_DEAD;
	if (lock(philo->state->mutex_someone_died))
		return (LOCK_ERR);
	if (philo->state->someone_died == 1)
		checker = OTHER_DIE;
	if (unlock(philo->state->mutex_someone_died))
		return (LOCK_ERR);
	return (checker);
}

int	check_done_eating(t_philo *philo)
{
	int checker;

	checker = 0;
	if (lock(philo->state->mutex_done_eating))
		return (LOCK_ERR);
	if (philo->state->done_eating == 1)
		checker = 1;
	if (unlock(philo->state->mutex_done_eating))
		return (LOCK_ERR);
	return (checker);
}

int	set_die_var(t_philo *philo)
{
	lock(philo->state->mutex_someone_died);
	philo->state->someone_died = SELF_DIE;
	unlock(philo->state->mutex_someone_died);
	philo->is_dead = 1;
	return (0);
}

int	set_meals(t_philo *philo)
{
	philo->meal_count++;
	if (philo->meal_count <= philo->state->meals_per_philo)
	{
		
		lock(philo->state->mutex_done_eating);
		philo->state->total_meals_still_needed--;
		if (philo->state->total_meals_still_needed == 0)
			philo->state->done_eating = 1;
		unlock(philo->state->mutex_done_eating);
	}
	return (0);
}
