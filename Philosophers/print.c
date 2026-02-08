/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:50:55 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/02 14:04:45 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *msg)
{
	long long	ts;

	pthread_mutex_lock(&philo->prog->print_mtx);
	if (!should_stop(philo->prog))
	{
		ts = now_ms() - philo->prog->start_ms;
		printf("%lld %d %s\n", ts, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->prog->print_mtx);
}
