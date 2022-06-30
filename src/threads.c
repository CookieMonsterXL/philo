/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:04:05 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/30 13:24:01 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_thread_func(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_n % 2 == 0)
		usleep(500);
	if (reset_die_timer(philo))
		return (NULL);
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
		if (philo->err != 0)
			return (NULL);
	}
	return (NULL);
}

int	wait_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{//PROTECT
		if (pthread_join(philo[i]->tid, NULL))
			return (ERR);
		i++;
	}
	return (0);
}

int	start_thread(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo)->state->number_of_philo > i)
	{
		if (pthread_create(&philo[i]->tid, NULL,
				philo_thread_func, (void *)philo[i]))
			return (ERR);
		i++;
	}
	return (0);
}
