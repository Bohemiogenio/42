/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:47:49 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/16 23:16:45 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	init_mutexes(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		if (pthread_mutex_init(&p->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&p->print_mtx, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&p->meal_mtx, NULL) != 0)
                return (1);
	if (pthread_mutex_init(&p->stop_mtx, NULL) != 0)
                return (1);
	return (0);
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
		p->philos[i].rigth_fork = &p->forks[(i + 1) % p->n_philo];
		i++;
	}
}

int	init_program(t_program *p)
{
	p->stop = 0;
	p->start_ms = 0;
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
		return (1);
	init_philos(p);
	return (0);
}
