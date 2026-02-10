/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:45:26 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 14:25:39 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void)
{
	struct	timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) +(tv.tv_usec / 1000LL));
}

void	precise_sleep(long long ms)
{
	long long	end;

	end = now_ms() + ms;
	while (now_ms() < end)
		usleep(200);
}

void	smart_sleep(long long ms, t_program *p)
{
	long long	 end;
	
	end = now_ms() + ms;
	while (!should_stop(p) && now_ms() < end)
		usleep(200);
}
