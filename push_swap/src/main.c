/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:04:57 by raulsanc          #+#    #+#             */
/*   Updated: 2025/10/05 15:31:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	prepare(int ac, char **av, t_node **a)
{
	if (ac < 2)
		return (2);
	if (!parse_args(ac, av, a))
	{
		ft_putstr_fd("Error\n", 2);
		ps_clear(a);
		return (1);
	}
	if (!*a || ps_issorted(*a))
	{
		ps_clear(a);
		return (2);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;
	int		code;

	a = NULL;
	b = NULL;
	code = prepare(ac, av, &a);
	if (code == 1)
		return (1);
	if (code == 2)
		return (0);
	if (ps_size(a) <= 5)
		sort_small(&a, &b);
	else
		sort_big(&a, &b);
	ps_clear(&a);
	ps_clear(&b);
	return (0);
}
