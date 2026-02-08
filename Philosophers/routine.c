/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:15:43 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/02 14:32:44 by raulsanc         ###   ########.fr       */
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
	t_philo *philo;

	philo = (t_philo *)arg;
	initial_delay(philo);
	while (!should_stop(philo->prog))
	{
		print_status(philo, "is thinking");
		precise_sleep(philo->prog->time_sleep);
		print_status(philo, "is sleeping");
		precise_sleep(philo->prog->time_sleep);
	}
	return (NULL);
}
