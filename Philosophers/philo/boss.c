/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:19:51 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 14:46:36 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_last_meal(t_philo *philo)
{
	long long	last;

	pthread_mutex_lock(&philo->prog->meal_mtx);
	last = philo->last_meal_ms;
	pthread_mutex_unlock(&philo->prog->meal_mtx);
	return (last);
}

static int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->prog->meal_mtx);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->prog->meal_mtx);
	return (meals);
}

static int	all_ate_enough(t_program *p)
{
	int	i;

	if (p->must_eat <= 0)
		return (0);
	i = 0;
	while (i < p->n_philo)
	{
		if (get_meals(&p->philos[i]) < p->must_eat)
			return (0);
		i++;
	}
	return (1);
}

static int	check_philo_death(t_philo *philo)
{
	long long	now;
	long long	last;
	long long	ts;

	now = now_ms();
	last = get_last_meal(philo);
	if (now - last > philo->prog->time_die)
	{
		set_stop(philo->prog);
		pthread_mutex_lock(&philo->prog->print_mtx);
		ts = now_ms() - philo->prog->start_ms;
		printf("%lld %d died\n", ts, philo->id);
		pthread_mutex_unlock(&philo->prog->print_mtx);
		return (1);
	}
	return (0);
}

void	*boss_routine(void *arg)
{
	t_program	*p;
	int			i;

	p = (t_program *)arg;
	while (!should_stop(p))
	{
		i = 0;
		while (i < p->n_philo)
		{
			if (check_philo_death(&p->philos[i]))
				return (NULL);
			i++;
		}
		if (all_ate_enough(p))
		{
			set_stop(p);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
