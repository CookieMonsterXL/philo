/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:39:43 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/20 14:25:48 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	timer(long interval_time)
{
	struct timeval	curr_time;
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
		perror_msg("Timefunc:");
	if (gettimeofday(&curr_time, NULL))
		perror_msg("Timefunc:");
	while (curr_time.tv_usec - start_time.tv_usec < interval_time * 1000)
	{
		usleep(250);
		if (gettimeofday(&curr_time, NULL))
			perror_msg("Timefunc:");
	}
	return (0);
}

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int	perror_msg(char *str)
{
	perror(str);
	exit(1);
}

int	action_print(t_philo *philo, char *str)
{
	lock(philo->mutex_print);
	ft_putstr_fd("Philo ", 1);
	ft_putnbr_fd(philo->philo_n, 1);
	ft_putstr_fd(str, 1);
	unlock(philo->mutex_print);
	return (0);
}

void	lock(pthread_mutex_t *key)
{
	int	error;
	
	error = pthread_mutex_lock(key);
	if (error == 0)
		return ;
	else if (error == EINVAL)
		error_msg("Error mutex lock: The value specified by mutex is invalid.\n");
	else if (error == EDEADLK)
		error_msg("Error mutex lock: A deadlock would occur if the thread blocked waiting for mutex.\n");
}

void	unlock(pthread_mutex_t *key)
{
	int	error;
	
	error = pthread_mutex_unlock(key);
	if (error == 0)
		return ;
	else if (error == EINVAL)
		error_msg("Error mutex unlock: The value specified by mutex is invalid.\n");
	else if (error == EPERM)
		error_msg("Error mutex unlock: The current thread does not hold a lock on mutex.\n");
}
