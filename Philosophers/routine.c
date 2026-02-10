/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:21:46 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 14:21:57 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initial_delay(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_delay(philo);
	while (!should_stop(philo->prog))
	{
		if (take_forks(philo))
			break ;
		philo_eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo->prog->time_sleep, philo->prog);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
