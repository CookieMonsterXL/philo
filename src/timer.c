/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/29 10:53:05 by tbouma           ###   ########.fr       */
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

	if (get_time(&start_timeval, &start_time))
		return (TIME_ERR);
	if (get_time(&curr_timeval, &curr_time))
		return (TIME_ERR);
	while (curr_time - start_time < interval_time * 1000)
	{
		usleep(500);
		if (get_time(&curr_timeval, &curr_time))
			return (TIME_ERR);
		checker = check_die_timer(philo);
		if (checker != NOT_DEAD)
			return (checker);
	}
	return (check_other_dead(philo));
}

int	start_program_time(t_state *state)
{
	return (get_time(&state->start_program_timeval,
			&state->start_program_timer));
}

int	reset_die_timer(t_philo *philo)
{
	get_time(&philo->start_die_timeval, &philo->start_die_timer);
	return (0);
}
