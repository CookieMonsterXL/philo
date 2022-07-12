/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:59:02 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/12 13:56:05 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

//FUNC RETURN VALUES
# define NOT_DEAD 0
# define SELF_DIE 1
# define OTHER_DIE 2
# define TIME_ERR 10
# define LOCK_ERR 20
# define MALLOC_ERR 30
# define ERR 40

//PRINT MSG
# define EAT "\t\tis eating\n"
# define SLEEP "\t\tis sleeping\n"
# define THINK "\t\tis thinking\n"
# define FORK "\t\thas taken a fork\n"
# define DIED "\t\tdied\n"

typedef struct s_state
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_per_philo;
	int					number_of_forks;
	int					total_meals_still_needed;
	pthread_mutex_t		**mutex_fork;
	bool				*bool_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_someone_died;
	pthread_mutex_t		*mutex_done_eating;
	int					someone_died;
	int					done_eating;
	struct timeval		start_program_timeval;
	long long			start_program_timer;
	struct timeval		curr_program_timeval;
	long long			curr_program_timer;
}	t_state;

typedef struct s_philo
{
	int					philo_n;
	int					is_dead;
	pthread_t			tid;
	t_state				*state;
	long long			start_die_timer;
	long long			current_die_timer;
	struct timeval		start_die_timeval;
	struct timeval		current_die_timeval;
	int					meal_count;
}	t_philo;

//INIT
int				init_philo(t_philo **philo, int index,
					t_state *state, int argc);
int				init_state(t_philo **philo, t_state *state,
					char **argv, int argc);
int				init_bool(t_state *state);
int				init_philo_arr(t_philo **philo, t_state *state, int argc);

//THREADS
void			*philo_thread_func(void *ptr);
int				wait_thread(t_philo **philo);
int				start_thread(t_philo **philo);

//PRINT
int				error_msg(char *str);
int				action_print(t_philo *philo, char *str);
int				print_die(t_philo *philo);

//FORK LOCK
int				fork_lock_1(t_philo *philo);
int				fork_lock_2(t_philo *philo);
int				fork_unlock_1(t_philo *philo);
int				fork_unlock_2(t_philo *philo);

//MUTEX LOCK
pthread_mutex_t	*make_mutex(pthread_mutex_t *mutex, int *checker);
pthread_mutex_t	*make_print_mutex(void);
pthread_mutex_t	*make_dead_mutex(void);
int				destroy_mutex(t_state *state);

//EAT SLEEP REPEAT
int				eat(t_philo *philo);
int				p_sleep(t_philo *philo);
int				die(t_philo *philo);

//SET CHECK VAR
int				set_die_var(t_philo *philo);
int				check_other_dead(t_philo *philo);
int				check_done_eating(t_philo *philo);
int				set_meals(t_philo *philo);
long			check_die_timer(t_philo *philo);

//TIMER
int				timer(t_philo *philo, long interval_time);
int				reset_die_timer(t_philo *philo);
long			current_time_stamp_ms(t_philo *philo);
int				get_time(struct timeval *timeval, long long *timestamp);

//FREE_DESTROY
int				all_free(t_philo **philo, t_state *state);

//CHECK IMPUT
int				check_input(int argc, char **argv);

//LIBFT
int				ft_putstr_fd(char *s, int fd);
int				ft_putnbr_fd(long long n, int fd);
int				ft_isdigit(int c);
int				ft_isspace(char c);
int				ft_atoi(const char *str);
int				ft_strlen(const char *s);

#endif