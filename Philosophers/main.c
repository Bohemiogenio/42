/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:44:03 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/16 20:30:16 by raulsanc         ###   ########.fr       */
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
	printf("INIT OK -> forks=%p philo=%p\n", (void *)p.forks, (void *)p.philos);
	printf("philo1: id=%d left=%p rigth=%p\n",
		p.philos[0].id, (void *)p.philos[0].left_fork, (void *)p.philos[0].rigth_fork);
	destroy_program(&p);
	return (0);
}
