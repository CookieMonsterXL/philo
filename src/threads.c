/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:04:05 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/29 11:04:38 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_thread_func(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_n % 2 == 0)
		usleep(500);
	reset_die_timer(philo);
	while (1)
	{
		if (check_other_dead(philo) == OTHER_DIE)
			return (NULL);
		if (check_done_eating(philo) == 1)
			return (NULL);
		if (check_die_timer(philo) != 0)
			return (NULL);
		if (eat(philo) != 0)
			return (NULL);
		if (p_sleep(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

void	wait_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		pthread_join(philo[i]->tid, NULL);
		i++;
	}
}

void	start_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		pthread_create(&philo[i]->tid, NULL,
			philo_thread_func, (void *)philo[i]);
		i++;
	}
}
