/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:58 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/29 12:02:55 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	*timestamp = make_time(timeval);
	return (0);
}

long long	make_time(struct timeval *timeval)
{
	long long	time;

	time = timeval->tv_sec % 10000;
	time *= 1000000;
	time += timeval->tv_usec;
	return (time);
}

// ongeveer 3 uur is 10.000 sec game time