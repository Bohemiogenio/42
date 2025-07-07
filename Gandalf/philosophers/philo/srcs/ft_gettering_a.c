/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:18:29 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:18:29 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_get_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_eat);
	philo->last_eat = ft_my_watch();
	pthread_mutex_unlock(&philo->mut_last_eat);
}

/*	The function ft_get_last_meal() gets the last meal time of the philosopher. 
	It receives a philosopher as an argument. It locks the mutex of the last 
	meal, input the current time as the last meal time, and unlocks the mutex
	of the last meal. */

void	ft_get_num_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_num_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->mut_num_meals);
}

/*	The function ft_get_num_meals() gets the number of meals of the philosopher.
	It receives a philosopher as an argument. It locks the mutex of the number 
	of meals, increments the number of meals, and unlocks the mutex of the 
	number of meals. */

uint64_t	ft_get_die(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_die_t);
	time = data->die_time;
	pthread_mutex_unlock(&data->mut_die_t);
	return (time);
}

/*	The function ft_get_die() gets the time to die of the philosopher. 
	It receives a data structure as an argument. It locks the mutex of the dying
	time, gets the dying time, and unlocks the mutex of the dying time. Finally,
	it returns the dying time. */

uint64_t	ft_get_eat(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_eat_t);
	time = data->eat_time;
	pthread_mutex_unlock(&data->mut_eat_t);
	return (time);
}

/*	The function ft_get_eat() gets the time to eat of the philosopher. 
	It receives a data structure as an argument. It locks the mutex of the 
	eating time, gets the eating time, and unlocks the mutex of the eating 
	time. Finally, it returns the eating time. */

uint64_t	ft_get_last_eat(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->mut_last_eat);
	time = philo->last_eat;
	pthread_mutex_unlock(&philo->mut_last_eat);
	return (time);
}

/*	The function ft_get_last_eat() gets the last meal time of the philosopher.
	It receives a philosopher as an argument. It locks the mutex of the last 
	meal, gets the last meal time, and unlocks the mutex of the last meal. 
	Finally, it returns the last meal time. */
