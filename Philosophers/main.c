/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:44:03 by raulsanc          #+#    #+#             */
/*   Updated: 2026/02/02 14:23:34 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_program	p;
	
	if (parse_args(ac, av, &p))
		return (1);
	if (init_program(&p))
	{
		write(2, "Error; init failed\n", 19);
		return (1);
	}
	if (start_simulation(&p))
	{
		write(2, "Error: simulation failed\n", 25);
		destroy_program(&p);
		return (1);
	}
	destroy_program(&p);
	return (0);
}
