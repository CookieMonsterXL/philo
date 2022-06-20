/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:59:02 by tiemen            #+#    #+#             */
/*   Updated: 2022/06/20 16:31:57 by tbouma           ###   ########.fr       */
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

//struct	t_state;
typedef struct s_state
{
    int 				number_of_philo;
    int					number_of_forks;
    int					time_to_die;
    int					time_to_sleep;
    int					time_to_eat;
	int					number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		**mutex_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_dead;
	int					someone_died;
}	t_state;

typedef struct s_philo
{
	int				philo_n;
	int				spoon;
	int				is_dead;
	int				has_eaten;
	int				timer_2;
	pthread_t		tid;
	t_state			*state;
	//pthread_mutex_t	*mutex_print;
}	t_philo;

//INIT
void	init_philo(t_philo **philo, int index,
			t_state *state);
void	init_state(t_state *state, char **argv);

//utils
int		timer(t_philo *philo, long interval_time);
int		d_timer(t_philo *philo, long interval_time);
int		error_msg(char *str);
int		perror_msg(char *str);
int		action_print(t_philo *philo, char *str);
void	lock(pthread_mutex_t *key);
void	unlock(pthread_mutex_t *key);
void	print_die(t_philo *philo);

//MUTEX
pthread_mutex_t	*make_print_mutex(void);
pthread_mutex_t	*make_dead_mutex(void);
int				destroy_mutex(t_state *state);

//EAT SLEEP REPEAT
int		eat(t_philo *philo);
int		p_sleep(t_philo *philo);
void	*die(void *ptr);

//TESTS
void	philo_print(t_philo **philo);

#endif