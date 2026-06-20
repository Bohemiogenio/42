/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:25:40 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 18:25:45 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks_partial(t_program *p, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
}

static void	destroy_forks(t_program *p)
{
	int	i;

	if (!p->forks)
		return ;
	i = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
	free(p->forks);
	p->forks = NULL;
}

void	destroy_program(t_program *p)
{
	if (!p)
		return ;
	destroy_forks(p);
	pthread_mutex_destroy(&p->print_mtx);
	pthread_mutex_destroy(&p->meal_mtx);
	pthread_mutex_destroy(&p->stop_mtx);
	free(p->philos);
	p->philos = NULL;
}
