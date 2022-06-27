/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/27 11:40:14 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	int checker;
	
	lock(philo->state->mutex_fork[philo->philo_n]);
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	checker = check_die_timer(philo);
	if (checker ==  0)
	{
		reset_die_timer(philo);
		action_print(philo, "\t\tis eating\n");
		checker = timer(philo, philo->state->time_to_eat);
	}

	
	// philo->meal_count++;
	// if (philo->meal_count <= philo->state->meals_per_philo)
	// {
	// 	philo->state->total_meals_still_needed--;
	// 	if (philo->state->total_meals_still_needed == 0)
	// 	{
	// 			lock(philo->state->mutex_someone_died);
	// 			philo->state->someone_died = SELF_DIE;
	// 			unlock(philo->state->mutex_someone_died);
	// 	}
		
	// }

	
	//action_print(philo, "\thas fork\n");
	unlock(philo->state->mutex_fork[philo->philo_n]);
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	return (checker);
}

int	p_sleep(t_philo *philo)
{
	int checker;
	
	checker = check_die_timer(philo);
	if (checker != 0)
		return (checker);
	action_print(philo, "\t\tis sleeping\n");
	checker = timer(philo, philo->state->time_to_sleep);
	return (checker);
}

int	die(t_philo *philo)
{
	if (check_other_dead(philo) == 2)
		return (OTHER_DIE);
	set_die_var(philo);
	lock(philo->state->mutex_print);
	print_die(philo);
	unlock(philo->state->mutex_print);
	return (SELF_DIE);
}

int	check_other_dead(t_philo *philo)
{
	int checker;

	checker = NOT_DEAD;
	lock(philo->state->mutex_someone_died);
	if (philo->state->someone_died == 1)
		checker = OTHER_DIE;
	unlock(philo->state->mutex_someone_died);
	return (checker);
}

void	set_die_var(t_philo *philo)
{
	philo->is_dead = 1;
	lock(philo->state->mutex_someone_died);
	philo->state->someone_died = SELF_DIE;
	unlock(philo->state->mutex_someone_died);
}
