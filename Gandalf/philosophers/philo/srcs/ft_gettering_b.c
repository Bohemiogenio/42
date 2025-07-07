/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettering_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 19:18:48 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 19:18:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_get_fork_l(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_l);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

/*	The function ft_get_fork_l() gets the left fork of the philosopher. It 
	receives a philosopher as an argument. If the philosopher is dead or 
	the philosopher is dying, it returns a failure message. Else, it locks 
	the mutex of the left fork, writes the message that the philosopher has 
	taken the forks, and returns a success message. */

int	ft_get_fork_r(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_r);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

/*	The function ft_get_fork_r() gets the right fork of the philosopher. It 
	receives a philosopher as an argument. If the philosopher is dead or the 
	philosopher is dying, it returns a failure message. Else, it locks the 
	mutex of the right fork, writes the message that the philosopher has taken 
	the forks, and returns a success message. */

int	get_forks(t_philo *philo)
{
	if (ft_num_philos(philo->data) == 1)
		return (ft_only_one(philo));
	if (ft_get_fork_r(philo) != 0)
		return (FAILURE);
	if (ft_get_fork_l(philo) != 0)
	{
		ft_drop_fork_r(philo);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*	The function get_forks() gets the forks of the philosopher. It receives a 
	philosopher as an argument. If there is only one philosopher, it calls the 
	function ft_only_one(). Else, it gets the right fork of the philosopher. 
	If the philosopher cannot get the right fork, it returns a failure message. 
	Else, it gets the left fork of the philosopher. If the philosopher cannot 
	get the left fork, it drops the right fork and returns a failure message. 
	Finally, it returns a success message. */
