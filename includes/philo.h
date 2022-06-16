/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 13:59:02 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/16 17:47:38 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int			philo_n;
	int			spoon;
	int			timer_1;
	int			timer_2;
	pthread_t	tid;
} t_philo;

typedef struct s_state
{
    int number_of_philo;	//One philo is one fork
    int number_of_forks;
    int time_to_die;		//If a philosopher didn’t start eating time_to_die
							//milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
    int time_to_sleep;		//The time a philosopher will spend sleeping.
    int time_to_eat;		//The time it takes for a philosopher to eat.
							//During that time, they will need to hold two forks.
	int	number_of_times_each_philosopher_must_eat; 
							//If all
							//philosophers have eaten at least number_of_times_each_philosopher_must_eat
							//times, the simulation stops. If not specified, the simulation stops when a
							//philosopher dies.
	t_philo	*philo_arr;
}	t_state;



//INIT
void	init_philo(t_philo *philo, int index);
void	init_state(t_state *state);


//TESTS
void	philo_print(t_state *state);



#endif