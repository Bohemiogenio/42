/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:35:34 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/16 18:44:51 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fill_program(int ac, char **av, t_program *p)
{
	p->n_philo = ft_atoi_positive(av[1]);
	p->time_die = ft_atoi_positive(av[2]);
	p->time_eat = ft_atoi_positive(av[3]);
	p->time_sleep = ft_atoi_positive(av[4]);
	p->must_eat = -1;
	if (p->n_philo <= 0 || p->time_die <= 0
		|| p->time_eat <= 0 || p->time_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		p->must_eat = ft_atoi_positive(av[5]);
		if (p->must_eat <= 0)
			return (1);
	}
	return (0);
}

int	parse_args(int ac, char **av, t_program *p)
{
	if (ac != 5 && ac != 6)
		return (write(2, "Error: wrong number of arguments\n", 33), 1);
	if (fill_program(ac, av, p))
		return (write(2, "Error: invalid arguments\n", 25), 1);
	return (0);
}
