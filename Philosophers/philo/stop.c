/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:26:41 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/02 13:31:37 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_program *p)
{
	int	val;

	pthread_mutex_lock(&p->stop_mtx);
	val = p->stop;
	pthread_mutex_unlock(&p->stop_mtx);
	return (val);
}

void	set_stop(t_program *p)
{
	pthread_mutex_lock(&p->stop_mtx);
	p->stop = 1;
	pthread_mutex_unlock(&p->stop_mtx);
}
