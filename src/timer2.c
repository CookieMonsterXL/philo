/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:58 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/30 14:14:41 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	current_time_stamp_ms(t_philo *philo)
{
	get_time(&philo->state->curr_program_timeval,
			&philo->current_die_timer, philo);
	return ((philo->current_die_timer
			- philo->state->start_program_timer) / 1000);
}

int	get_time(struct timeval *timeval, long long *timestamp, t_philo *philo)
{
	if (gettimeofday(timeval, NULL))
	{
		philo->err = TIME_ERR;
		pthread_mutex_lock(philo->state->mutex_someone_died);
		philo->state->someone_died = 1;
		pthread_mutex_unlock(philo->state->mutex_someone_died);
		return (TIME_ERR);
	}
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