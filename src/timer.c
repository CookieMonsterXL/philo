/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/30 12:30:33 by tbouma           ###   ########.fr       */
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

	if (get_time(&start_timeval, &start_time, philo))
		return (TIME_ERR);
	if (get_time(&curr_timeval, &curr_time, philo))
		return (TIME_ERR);
	while (curr_time - start_time < interval_time * 1000)
	{
		usleep(500);
		if (get_time(&curr_timeval, &curr_time, philo))
			return (TIME_ERR);
		checker = check_die_timer(philo);
		if (philo->err != 0)
			return (TIME_ERR);
		if (checker != NOT_DEAD)
			return (checker);
	}
	return (check_other_dead(philo));
}

int	start_program_time(t_philo *philo)
{
	return (get_time(&philo->state->start_program_timeval,
			&philo->state->start_program_timer, philo));
}

int	reset_die_timer(t_philo *philo)
{
	if (get_time(&philo->start_die_timeval, &philo->start_die_timer, philo))
		return (TIME_ERR);
	return (0);
}
