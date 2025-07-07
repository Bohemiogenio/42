/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:22:03 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:22:03 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_keep_or_not(t_data *data)
{
	bool	keep;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep);
}

/* The function ft_keep_or_not() checks if the program should keep iterating. 
   That is, if the program should keep running. It receives a data structure as
   an argument. It locks the mutex of the flag to keep iterating, gets the flag
   to keep iterating, and unlocks the mutex of the flag to keep iterating. 
   Finally, it returns the flag to keep iterating. */

bool	ft_has_eaten(t_data *value, t_philo *philo)
{
	bool	res;

	res = false;
	if (ft_times_eating(philo) >= value->nb_meals)
		res = true;
	return (res);
}

/* The function ft_has_eaten() checks if the philosopher has eaten the number 
   of times specified. 
   It receives a data structure and a philosopher as arguments. 
   It checks if the number of times the philosopher has eaten is greater than or
   equal to the number of meals specified. If the number of times the 
   philosopher has eaten is greater than or equal to the number of meals 
   specified, it returns true. Otherwise, it returns false. */

bool	ft_rip(t_philo *philo)
{
	bool		res;
	t_data		*data;

	data = philo->data;
	res = false;
	if (ft_my_watch() - ft_get_last_eat(philo) > ft_get_die(data)
		&& ft_how_are_you(philo) != EATING)
	{
		ft_status(philo, DIE);
		res = true;
	}
	return (res);
}

/* The function ft_rip() checks if the philosopher is dead. It receives a 
   philosopher as an argument. It gets the data structure of the philosopher. 
   It checks if the time since the last meal of the philosopher is greater than
   the time to die and if the philosopher is not eating. If the time since the 
   last meal of the philosopher is greater than the time to die and the 
   philosopher is not eating, it changes the state of the philosopher to dead 
   and returns true. Otherwise, it returns false. */

bool	ft_num_meals(t_data *value)
{
	if (value->nb_meals > 0)
		return (true);
	return (false);
}

/* The function ft_num_meals() checks if the number of meals is greater than 0.
   It receives a data structure as an argument. If the number of meals is 
   greater than 0, it returns true. Otherwise, it returns false. */
