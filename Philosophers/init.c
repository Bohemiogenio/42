/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:40:08 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 18:40:12 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks_partial(t_program *p, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
}

static int	init_control_mutexes(t_program *p)
{
	if (pthread_mutex_init(&p->print_mtx, NULL) != 0)
		return (destroy_forks_partial(p, p->n_philo), 1);
	if (pthread_mutex_init(&p->meal_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&p->print_mtx);
		destroy_forks_partial(p, p->n_philo);
		return (1);
	}
	if (pthread_mutex_init(&p->stop_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&p->meal_mtx);
		pthread_mutex_destroy(&p->print_mtx);
		destroy_forks_partial(p, p->n_philo);
		return (1);
	}
	return (0);
}

static int	init_mutexes(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		if (pthread_mutex_init(&p->forks[i], NULL) != 0)
		{
			destroy_forks_partial(p, i);
			return (1);
		}
		i++;
	}
	return (init_control_mutexes(p));
}

static void	init_philos(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		p->philos[i].id = i + 1;
		p->philos[i].meals_eaten = 0;
		p->philos[i].last_meal_ms = 0;
		p->philos[i].prog = p;
		p->philos[i].left_fork = &p->forks[i];
		p->philos[i].right_fork = &p->forks[(i + 1) % p->n_philo];
		i++;
	}
}

int	init_program(t_program *p)
{
	p->stop = 0;
	p->start_ms = 0;
	p->forks = NULL;
	p->philos = NULL;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->n_philo);
	if (!p->forks)
		return (1);
	p->philos = malloc(sizeof(t_philo) * p->n_philo);
	if (!p->philos)
	{
		free(p->forks);
		p->forks = NULL;
		return (1);
	}
	if (init_mutexes(p))
	{
		free(p->philos);
		free(p->forks);
		p->philos = NULL;
		p->forks = NULL;
		return (1);
	}
	init_philos(p);
	return (0);
}
