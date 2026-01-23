/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raul <raulsanc@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:59:51 by Raul              #+#    #+#             */
/*   Updated: 2026/01/23 16:41:45 by Raul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1999LL));
}

int	should_stop(t_program *p)
{
	int	val;

	pthread_mutex_lock(&p->stop_mtx);
	val = p->stop;
	pthread_mutex_unlock(&p->stop_mtx);
	return (val);
}

void	precise_sleep(long long ms, t_program *p)
{
	long long	end;

	end = now_ms() + ms;
	while (!should_stop(p))
	{
		if (now_ms() >= end)
			break ;
		if ((end - now_ms()) > 10)
			usleep(1000);
		else
			usleep(200);
	}
}
