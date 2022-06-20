/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:58:47 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 17:17:29 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo *philo)
{
	lock(philo->state->mutex_fork[philo->philo_n]);
	lock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	pthread_create(&philo->tid, NULL, die, (void *)philo); //start dead timer
	action_print(philo, " is eating\n");
	if (timer(philo, philo->state->time_to_eat))
	{
		lock(philo->state->mutex_dead);
		print_die(philo);
		unlock(philo->state->mutex_dead);
	}
	philo->has_eaten = 1;
	unlock(philo->state->mutex_fork[philo->philo_n]);
	unlock(philo->state->mutex_fork[(philo->philo_n + 1) % philo->state->number_of_philo]);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	action_print(philo, " is sleeping\n");
	if (timer(philo, philo->state->time_to_sleep))
	{
		lock(philo->state->mutex_dead);
		print_die(philo);
		unlock(philo->state->mutex_dead);
	}
	return (0);
}

void	*die(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (d_timer(philo, philo->state->time_to_die))
		return (ptr);
	if (philo->has_eaten == 0)
	{
		philo->is_dead = 1;
		philo->state->someone_died = 1;
	}
	pthread_exit(0);//exit(0);
	return (ptr);
}
