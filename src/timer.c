/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/30 13:53:02 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	timer(t_philo *philo, long interval_time)
{
	int					checker;
	struct timeval		curr_timeval;
	struct timeval		start_timeval;
	long long			curr_time;
	long long			start_time;

	get_time(&start_timeval, &start_time, philo);
	get_time(&curr_timeval, &curr_time, philo);
	while (curr_time - start_time < interval_time * 1000)
	{
		usleep(500);
		get_time(&curr_timeval, &curr_time, philo);
		checker = check_die_timer(philo);
		if (checker != NOT_DEAD)
			return (checker);
	}
	return (check_other_dead(philo));
}

int	start_program_time(t_philo **philo)
{
	return (get_time(&philo[0]->state->start_program_timeval,
			&philo[0]->state->start_program_timer, philo[0]));
}

int	reset_die_timer(t_philo *philo)
{
	get_time(&philo->start_die_timeval, &philo->start_die_timer, philo);
	return (0);
}
