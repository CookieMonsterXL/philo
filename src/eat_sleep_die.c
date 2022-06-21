/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_die.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 12:58:47 by tbouma        #+#    #+#                 */
/*   Updated: 2022/06/21 19:17:31 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	lock(philo->state->mutex_fork[philo->philo_n]);
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	
	action_print(philo, "\thas fork\n");
	philo->start_eating = 1;
	while(philo->reset_timer == 0)
		usleep(250);
	philo->reset_timer = 0;
	action_print(philo, "\tis eating\n");
	if (timer(philo, philo->state->time_to_eat))
	{
		lock(philo->state->mutex_die_print);
		print_die(philo);
		unlock(philo->state->mutex_die_print);
	}
	unlock(philo->state->mutex_fork[philo->philo_n]);
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	action_print(philo, "\tis sleeping\n");
	if (timer(philo, philo->state->time_to_sleep))
	{
		lock(philo->state->mutex_die_print);
		print_die(philo);
		unlock(philo->state->mutex_die_print);
	}
	return (0);
}

void	*die(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (d_timer(philo, philo->state->time_to_die))
		return (ptr);
	if (philo->start_eating == 0)
	{
		philo->is_dead = 1;
		lock(philo->state->mutex_someone_died);
		philo->state->someone_died = 1;
		unlock(philo->state->mutex_someone_died);
	}
	pthread_exit(0);//exit(0);
	return (ptr);
}
