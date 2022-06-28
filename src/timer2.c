/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timer2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:34:58 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/28 17:35:14 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	current_time_stamp_ms(t_philo *philo)
{
	if (get_time(&philo->state->curr_program_timeval, &philo->current_die_timer))
		return (TIME_ERR);
	return ((philo->current_die_timer - philo->state->start_program_timer) / 1000);
}

int	get_time(struct timeval	*timeval, long long *timestamp) //TIMEVAL gets set, TIMESTAMP is made
{
	if (gettimeofday(timeval, NULL))
	{
		perror_msg("Timefunc:");
		return (TIME_ERR);
	}
	*timestamp = make_time(timeval);
	return (0);
}

long long make_time(struct timeval	*timeval)
{
	long long	time;

	time = timeval->tv_sec % 10000; // ongeveer 3 uur is 10.000 sec game time
	time *= 1000000;
	time += timeval->tv_usec;
	return (time);
}