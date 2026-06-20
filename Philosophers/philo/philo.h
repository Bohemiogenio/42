/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:13:02 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 17:45:32 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_ms;
	int				meals_eaten;
	t_program		*prog;
}	t_philo;

typedef struct s_program
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		start_ms;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	meal_mtx;
	pthread_mutex_t	stop_mtx;
	t_philo			*philos;
}	t_program;

/* PARSE */
int			parse_args(int ac, char **a, t_program *p);
int			ft_atoi_positive(const char *s);

/* INIT / DESTROY */
int			init_program(t_program *p);
void		destroy_program(t_program *p);
void		destroy_forks_partial(t_program *p, int count);

/* STOP */
int			should_stop(t_program *p);
void		set_stop(t_program *p);

/* PRINT */
void		print_status(t_philo *philo, const char *msg);

/* TIME */
long long	now_ms(void);
void		smart_sleep(long long ms, t_program *p);

/* SIMULATION */
int			start_simulation(t_program *p);
void		*philo_routine(void *arg);

/* BOSS */
void		*boss_routine(void *arg);

/* SPLIT */
int			take_forks(t_philo *philo);
void		philo_eat(t_philo *philo);

#endif
