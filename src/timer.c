/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/23 12:22:05 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	timer(t_philo *philo, long interval_time)
{
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
		usleep(250);
		if (get_time(&curr_timeval, &curr_time))
			return (TIME_ERR);
		if (check_die_timer(philo) ==  SELF_DIE)
			return (SELF_DIE);
		lock(philo->state->mutex_someone_died);
		if (philo->state->someone_died == SELF_DIE && philo->is_dead == NOT_DEAD)
		{
			unlock(philo->state->mutex_someone_died);
			return (OTHER_DIE);
		}	
		unlock(philo->state->mutex_someone_died);
	}
	return (0);
}

long	current_time_stamp_ms(t_philo *philo)
{
	if (get_time(&philo->state->curr_program_timeval, &philo->current_die_timer))
		return (TIME_ERR);
	return ((philo->current_die_timer - philo->state->start_program_timer) / 1000);
}

int	start_program_time(t_state *state)
{
	return (get_time(&state->start_program_timeval, &state->start_program_timer));
}

long	check_die_timer(t_philo *philo)
{
	if (get_time(&philo->current_die_timeval, &philo->current_die_timer))
		return (TIME_ERR);
	if (((philo->current_die_timer - philo->start_die_timer) / 1000) > philo->state->time_to_die)
	{
		philo->is_dead = 1;
		return (SELF_DIE);
	}
	else
		return (NOT_DEAD);
}

int	reset_die_timer(t_philo *philo)
{
	return (get_time(&philo->start_die_timeval, &philo->start_die_timer));
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
