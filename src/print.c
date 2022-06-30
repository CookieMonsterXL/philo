/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:02:20 by tbouma            #+#    #+#             */
/*   Updated: 2022/06/30 11:59:25 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	perror_msg(char *str)
{
	perror(str);
	return (0);
}

int	print_die(t_philo *philo)
{
	long	curr_time;

	curr_time = current_time_stamp_ms(philo);
	if (philo->err != 0)
	{
		pthread_mutex_unlock(philo->state->mutex_print);
		return (TIME_ERR);
	}
	ft_putnbr_fd(curr_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->philo_n + 1, 1);
	ft_putstr_fd(DIED, 1);
	return (0);
}

int	action_print(t_philo *philo, char *str)
{
	long	curr_time;

	if (check_other_dead(philo) == OTHER_DIE)
		return (0);
	if (check_done_eating(philo) == 1)
		return (0);
	pthread_mutex_lock(philo->state->mutex_print);
	curr_time = current_time_stamp_ms(philo);
	if (philo->err != 0)
	{
		pthread_mutex_unlock(philo->state->mutex_print);
		return (TIME_ERR);
	}
	ft_putnbr_fd(curr_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->philo_n + 1, 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(philo->state->mutex_print);
	return (0);
}
