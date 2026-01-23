/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:44:03 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/23 16:12:29 by Raul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_program	p;
	long long	t0;
	long long	t1;
	
	if (parse_args(ac, av, &p))
		return (1);
	if (init_program(&p))
	{
		write(2, "Error; init failed\n", 19);
		return (1);
	}

	t0 = now_ms();
	precise_sleep(300, &p);
	t1 = now_ms();
	printf("slept ~%lld ms\n", (t1 - t0));

	destroy_program(&p);
	return (0);
}
