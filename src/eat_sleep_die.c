/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/23 12:09:24 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	int checker;
	lock(philo->state->mutex_fork[philo->philo_n]);
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	if (check_die_timer(philo) ==  1)
		return (1);
	//action_print(philo, "\thas fork\n");
	action_print(philo, "\tis eating\n");
	reset_die_timer(philo);
	checker = timer(philo, philo->state->time_to_eat);
	unlock(philo->state->mutex_fork[philo->philo_n]);
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	if (check_die_timer(philo) ==  SELF_DIE)
		return (SELF_DIE);
	return (checker);
}

int	p_sleep(t_philo *philo)
{
	int checker;
	action_print(philo, "\tis sleeping\n");
	checker = timer(philo, philo->state->time_to_sleep);
	if (check_die_timer(philo) ==  SELF_DIE)
		return (SELF_DIE);
	return (checker);
}

int	die(t_philo *philo)
{
	int checker;
	
	checker = check_other_dead(philo);
	set_die_var(philo);
	lock(philo->state->mutex_die_print);
	if (checker == NOT_DEAD)
	{
		print_die(philo);
		checker = SELF_DIE;
	}
	unlock(philo->state->mutex_die_print);
	return (checker);
}

int	check_other_dead(t_philo *philo)
{
	int checker;
	lock(philo->state->mutex_someone_died);
	if (philo->state->someone_died == 1)
		checker = OTHER_DIE;
	else
		checker = SELF_DIE;
	unlock(philo->state->mutex_someone_died);
	return (checker);
}

void	set_die_var(t_philo *philo)
{
	lock(philo->state->mutex_someone_died);
	philo->state->someone_died = SELF_DIE;
	unlock(philo->state->mutex_someone_died);
}
