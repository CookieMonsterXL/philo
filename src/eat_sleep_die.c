/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_die.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 12:58:47 by tbouma        #+#    #+#                 */
/*   Updated: 2022/06/27 20:32:54 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	int checker;
	
	lock(philo->state->mutex_fork[philo->philo_n]);
	action_print(philo, "\t\thas taken a fork\n");
	
	if (philo->state->number_of_philo == 1)
	{
		usleep(philo->state->time_to_die * 950);
		unlock(philo->state->mutex_fork[philo->philo_n]);
		return (0);
	}
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	action_print(philo, "\t\thas taken a fork\n");
	checker = check_die_timer(philo);
	if (checker ==  0)
	{
		action_print(philo, "\t\tis eating\n");
		if (philo->meal_count >= 0)
			set_meals(philo);
		reset_die_timer(philo);
		checker = timer(philo, philo->state->time_to_eat);
	}

	
	unlock(philo->state->mutex_fork[philo->philo_n]);
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	//action_print(philo, "\t\tDONE EATING\n");//debug
	return (checker);
}

int	p_sleep(t_philo *philo)
{
	int checker;
	
	// checker = check_die_timer(philo);
	// if (checker != 0)
	// 	return (checker);
	action_print(philo, "\t\tis sleeping\n");
	checker = timer(philo, philo->state->time_to_sleep);
	action_print(philo, "\t\tis thinking\n");
	//action_print(philo, "\t\tDONE SLEEPING\n");//DEBUG
	return (checker);
}

int	die(t_philo *philo)
{
	int checker;
	
	checker = check_other_dead(philo);
	if (checker != 0)
		return (checker);
	checker = set_die_var(philo);
	lock(philo->state->mutex_print);
	print_die(philo);
	unlock(philo->state->mutex_print);
	return (SELF_DIE);
}

int	check_other_dead(t_philo *philo)
{
	int checker;

	checker = NOT_DEAD;
	// if (lock(philo->state->mutex_someone_died))
	// 	return (LOCK_ERR);
	if (philo->state->someone_died == 1)
		checker = OTHER_DIE;
	// if (unlock(philo->state->mutex_someone_died))
	// 	return (LOCK_ERR);
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

int	check_done_eating(t_philo *philo)
{
	int checker;

	checker = 0;
	// if (lock(philo->state->mutex_done_eating))
	// 	return (LOCK_ERR);
	if (philo->state->done_eating == 1)
		checker = 1;
	// if (unlock(philo->state->mutex_done_eating))
	// 	return (LOCK_ERR);
	return (checker);
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
