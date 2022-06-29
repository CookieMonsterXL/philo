/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/29 12:51:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	int	checker;

	fork_lock_1(philo);
	action_print(philo, FORK);
	if (philo->state->number_of_philo == 1)
	{
		checker = timer(philo, philo->state->time_to_die + 2);
		pthread_mutex_unlock(philo->state->mutex_fork[philo->philo_n]);
		return (0);
	}
	fork_lock_2(philo);
	action_print(philo, FORK);
	checker = check_die_timer(philo);
	if (checker == 0)
	{
		reset_die_timer(philo);
		action_print(philo, EAT);
		if (philo->meal_count >= 0)
			set_meals(philo);
		checker = timer(philo, philo->state->time_to_eat);
	}
	fork_unlock_1(philo);
	fork_unlock_2(philo);
	return (checker);
}

int	p_sleep(t_philo *philo)
{
	int	checker;

	action_print(philo, SLEEP);
	checker = timer(philo, philo->state->time_to_sleep);
	action_print(philo, THINK);
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
	print_die(philo);
	pthread_mutex_unlock(philo->state->mutex_print);
	return (SELF_DIE);
}
