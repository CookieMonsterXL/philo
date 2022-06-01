/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/01 19:26:22 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/01 19:56:01 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_stats
{
    int number_of_philo;
    int number_of_forks;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
}	t_stats;

int philo_thread_func(void *ptr)
{
	t_stats *state;
	
	state = (t_stats *)ptr;
	
	
}

int main(int argc, char **argv)
{
	t_stats	state;
	
    pthread_t   new_thread;
    
    state.number_of_philo = 5;
    state.number_of_forks = state.number_of_philo;
    state.time_to_die = 100;
    state.time_to_sleep = 100;
    state.time_to_eat = 100;

    while (state.number_of_philo > i)
    {
        pthread_create(new_thread, NULL, philo_thread_func, &state);
        i++;
        
    }
}