/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:22:34 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/04 14:22:46 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->meal_mtx);
	philo->last_meal_ms = now_ms();
	pthread_mutex_unlock(&philo->prog->meal_mtx);
}

static void	inc_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->meal_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->prog->meal_mtx);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	set_last_meal(philo);
	print_status(philo, "is eating");
	smart_sleep(philo->prog->time_eat, philo->prog);
	inc_meals(philo);
	unlock_forks(philo);
}
