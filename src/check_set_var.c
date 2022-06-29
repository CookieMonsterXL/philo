/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_set_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:57:14 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/29 12:49:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	check_die_timer(t_philo *philo)
{
	int	checker;

	checker = 0;
	get_time(&philo->current_die_timeval, &philo->current_die_timer);
	if (((philo->current_die_timer - philo->start_die_timer))
		> philo->state->time_to_die * 1000)
	{
		checker = die(philo);
		return (checker);
	}
	else
		return (checker);
}

int	check_other_dead(t_philo *philo)
{
	int	checker;

	checker = NOT_DEAD;
	pthread_mutex_lock(philo->state->mutex_someone_died);
	if (philo->state->someone_died == 1)
		checker = OTHER_DIE;
	pthread_mutex_unlock(philo->state->mutex_someone_died);
	return (checker);
}

int	check_done_eating(t_philo *philo)
{
	int	checker;

	checker = 0;
	pthread_mutex_lock(philo->state->mutex_done_eating);
	if (philo->state->done_eating == 1)
		checker = 1;
	pthread_mutex_unlock(philo->state->mutex_done_eating);
	return (checker);
}

int	set_die_var(t_philo *philo)
{
	pthread_mutex_lock(philo->state->mutex_someone_died);
	philo->state->someone_died = SELF_DIE;
	pthread_mutex_unlock(philo->state->mutex_someone_died);
	philo->is_dead = 1;
	return (0);
}

int	set_meals(t_philo *philo)
{
	philo->meal_count++;
	if (philo->meal_count <= philo->state->meals_per_philo)
	{
		pthread_mutex_lock(philo->state->mutex_done_eating);
		philo->state->total_meals_still_needed--;
		if (philo->state->total_meals_still_needed == 0)
			philo->state->done_eating = 1;
		pthread_mutex_unlock(philo->state->mutex_done_eating);
	}
	return (0);
}
