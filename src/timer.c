/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:00:37 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/20 17:00:53 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	timer(t_philo *philo, long interval_time)
{
	struct timeval	curr_time;
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
		perror_msg("Timefunc:");
	if (gettimeofday(&curr_time, NULL))
		perror_msg("Timefunc:");
	while (curr_time.tv_usec - start_time.tv_usec < interval_time * 1000)
	{
		if (philo->state->someone_died == 1 && philo->is_dead == 0)
			pthread_exit(0);//exit(0);
		if (philo->is_dead == 1)
			return (1);
		usleep(250);
		if (gettimeofday(&curr_time, NULL))
			perror_msg("Timefunc:");
	}
	return (0);
}

int	d_timer(t_philo *philo, long interval_time)
{
	struct timeval	curr_time;
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
		perror_msg("Timefunc:");
	if (gettimeofday(&curr_time, NULL))
		perror_msg("Timefunc:");
	while (curr_time.tv_usec - start_time.tv_usec < interval_time * 1000)
	{
		if (philo->state->someone_died == 1 && philo->is_dead == 0)
			pthread_exit(0);//exit(0);
		if (philo->has_eaten == 1)
			return (1);
		usleep(250);
		if (gettimeofday(&curr_time, NULL))
			perror_msg("Timefunc:");
	}
	return (0);
}
