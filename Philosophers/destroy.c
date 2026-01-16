/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:19:20 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/16 20:35:03 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_program(t_program *p)
{
	int	i;

	i = 0;
	if (p->forks)
	{
		while (i < p->n_philo)
		{
			pthread_mutex_destroy(&p->forks[i]);
			i++;
		}
		free(p->forks);
		p->forks = NULL;
	}
	pthread_mutex_destroy(&p->print_mtx);
	pthread_mutex_destroy(&p->meal_mtx);
	pthread_mutex_destroy(&p->stop_mtx);
	if (p->philos)
	{
		free(p->philos);
		p->philos = NULL;
	}
}
