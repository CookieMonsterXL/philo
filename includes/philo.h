/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 13:59:02 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/22 18:32:02 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>

# define	NOT_DEAD	0
# define	SELF_DIE	1
# define	OTHER_DIE	2
//struct	t_state;
typedef struct s_state
{
    int 				number_of_philo; 	//Arg	1
    int					time_to_die; 		//		2
    int					time_to_eat;		//		3
    int					time_to_sleep;		//		4
	int					number_of_times_each_philosopher_must_eat;	//5
    int					number_of_forks;
	pthread_mutex_t		**mutex_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_die_print;
	pthread_mutex_t		*mutex_someone_died;
	int					someone_died;
	struct timeval		start_program;
}	t_state;

typedef struct s_philo
{
	int				philo_n;
	int				spoon;
	int				is_dead;
	int				start_eating;
	int				reset_timer;
	pthread_t		tid;
	t_state			*state;
	pthread_mutex_t		*mutex_eat;
	//pthread_mutex_t	*mutex_print;
	struct timeval		start_die_timer;
	struct timeval		current_die_timer;
}	t_philo;

//INIT
void	init_philo(t_philo **philo, int index,
			t_state *state);
void	init_state(t_state *state, char **argv);

//utils
int		error_msg(char *str);
int		perror_msg(char *str);
int		action_print(t_philo *philo, char *str);
void	lock(pthread_mutex_t *key);
void	unlock(pthread_mutex_t *key);
void	print_die(t_philo *philo);

//MUTEX
pthread_mutex_t	*make_mutex(pthread_mutex_t *mutex);
pthread_mutex_t	*make_print_mutex(void);
pthread_mutex_t	*make_dead_mutex(void);
int				destroy_mutex(t_state *state);

//EAT SLEEP REPEAT
int		eat(t_philo *philo);
int		p_sleep(t_philo *philo);
int	die(t_philo *philo);

void	set_die_var(t_philo *philo);
int	check_other_dead(t_philo *philo);


//TIMER
int		start_program_time(t_state *state);
long	current_time_stamp(t_philo *philo);
int		timer(t_philo *philo, long interval_time);
int		d_timer(t_philo *philo, long interval_time);

long	check_die_timer(t_philo *philo);
int	reset_die_timer(t_philo *philo);

//TESTS
void	philo_print(t_philo **philo);

#endif