/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/30 12:38:29 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	eat2(t_philo *philo, int checker)
{
	if (checker == 0)
	{
		reset_die_timer(philo);
		if (philo->err != 0)
			return (philo->err);
		action_print(philo, EAT);
		if (philo->err != 0)
			return (philo->err);
		if (philo->meal_count >= 0)
			set_meals(philo);
		checker = timer(philo, philo->state->time_to_eat);
	}
	return (checker);
}

int	eat(t_philo *philo)
{
	int	checker;

	fork_lock_1(philo);
	action_print(philo, FORK);
	if (philo->err != 0)
		return (philo->err);
	if (philo->state->number_of_philo == 1)
	{
		checker = timer(philo, philo->state->time_to_die + 2);
		pthread_mutex_unlock(philo->state->mutex_fork[philo->philo_n]);
		return (0);
	}
	fork_lock_2(philo);
	action_print(philo, FORK);
	if (philo->err != 0)
		return (philo->err);
	checker = check_die_timer(philo);
	if (philo->err != 0)
		return (philo->err);
	if (eat2(philo, checker))
		return (ERR);
	fork_unlock_1(philo);
	fork_unlock_2(philo);
	return (checker);
}

int	p_sleep(t_philo *philo)
{
	int	checker;

	action_print(philo, SLEEP);
	if (philo->err != 0)
		return (philo->err);
	checker = timer(philo, philo->state->time_to_sleep);
	action_print(philo, THINK);
	if (philo->err != 0)
		return (philo->err);
	return (checker);
}

int	die(t_philo *philo)
{
	int	checker;

	checker = check_other_dead(philo);
	if (checker != 0)
		return (checker);
	checker = set_die_var(philo);
	usleep(50);
	pthread_mutex_lock(philo->state->mutex_print);
	if (print_die(philo))
	{
		pthread_mutex_unlock(philo->state->mutex_print);
		return (TIME_ERR);
	}
	pthread_mutex_unlock(philo->state->mutex_print);
	return (SELF_DIE);
}
