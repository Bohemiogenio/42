/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:04:59 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 12:55:18 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		if (pthread_create(&p->philos[i].thread, NULL,
				philo_routine, &p->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	join_threads(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		pthread_join(p->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_program *p)
{
	int			i;
	pthread_t	boss;

	p->start_ms = now_ms();
	i = 0;
	while (i < p->n_philo)
	{
		p->philos[i].last_meal_ms = p->start_ms;
		i++;
	}
	if (create_threads(p))
		return (1);
	if (pthread_create(&boss, NULL, boss_routine, p) != 0)
		return (1);
	pthread_join(boss, NULL);
	join_threads(p);
	return (0);
}
