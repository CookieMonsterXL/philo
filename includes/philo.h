/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbouma <tbouma@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 13:59:02 by tiemen        #+#    #+#                 */
/*   Updated: 2022/06/24 15:37:04 by tiemen        ########   odam.nl         */
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
# include <stdbool.h>

//FUNC RETURN VALUES
# define	NOT_DEAD	0
# define	SELF_DIE	1
# define	OTHER_DIE	2
# define	TIME_ERR	10


// Colors

# define RESET "\e[0m"
# define PINK "\e[0;38;5;199m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"

/*
** Error messages
*/
# define NUM_ARGS "ERROR: The number of argments must be 4 or 5"
# define ARG1 "ERROR: There is a mistake in number of philosophers"
# define ARG2 "ERROR: There is a mistake in time to die"
# define ARG3 "ERROR: There is a mistake in time to eat"
# define ARG4 "ERROR: There is a mistake in time to sleep"
# define ARG5 "ERROR: There is a mistake in number of times each \
philosopher must eat"

/*
** Help message
*/
# define HELP "The number of argments must be 4 or 5:\n\
- arg1 number of philosophers\n\
- arg2 time to die\n\
- arg3 time to eat\n\
- arg4 time to sleep\n\
- arg5 number of times each philosopher must eat (optional)"

/*
** Routines messages
*/
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died ☠️"

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
	bool				*bool_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_die_print;
	pthread_mutex_t		*mutex_someone_died;
	int					someone_died;
	struct timeval		start_program_timeval;
	long long			start_program_timer;
	struct timeval		curr_program_timeval;
	long long			curr_program_timer;
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
	long long		start_die_timer;
	long long		current_die_timer;
	struct timeval		start_die_timeval;
	struct timeval		current_die_timeval;

	int				curr_timestamp_print;
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
int		eat_lefty(t_philo *philo);
int		p_sleep(t_philo *philo);
int	die(t_philo *philo);

void	set_die_var(t_philo *philo);
int	check_other_dead(t_philo *philo);


//TIMER
int		start_program_time(t_state *state);
long	current_time_stamp_ms(t_philo *philo);
int		timer(t_philo *philo, long interval_time);
int		d_timer(t_philo *philo, long interval_time);

long		check_die_timer(t_philo *philo);
int			reset_die_timer(t_philo *philo);
long long	make_time(struct timeval	*timeval);
int			get_time(struct timeval	*timeval, long long *timestamp);

//TESTS
void	philo_print(t_philo **philo);

#endif