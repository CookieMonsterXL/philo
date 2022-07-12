/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/12 09:48:27 by tbouma           ###   ########.fr       */
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

	get_time(&start_timeval, &start_time);
	get_time(&curr_timeval, &curr_time);
	while (curr_time - start_time < interval_time * 1000)
	{
		usleep(500);
		get_time(&curr_timeval, &curr_time);
		checker = check_die_timer(philo);
		if (checker != NOT_DEAD)
			return (checker);
	}
	return (check_other_dead(philo));
}

int	reset_die_timer(t_philo *philo)
{
	get_time(&philo->start_die_timeval, &philo->start_die_timer);
	return (0);
}

long	current_time_stamp_ms(t_philo *philo)
{
	get_time(&philo->state->curr_program_timeval,
		&philo->current_die_timer);
	return ((philo->current_die_timer
			- philo->state->start_program_timer) / 1000);
}

int	get_time(struct timeval *timeval, long long *timestamp)
{
	gettimeofday(timeval, NULL);
	*timestamp = timeval->tv_sec % 10000;
	*timestamp *= 1000000;
	*timestamp += timeval->tv_usec;
	return (0);
}
// ongeveer 3 uur is 10.000 sec game time