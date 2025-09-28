/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:35 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/29 01:13:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	swap_head(t_node **s)
{
	t_node	*first;
	t_node	*second;

	if (!s || !*s || !(*s)->next)
		return (0);
	first = *s;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*s = second;
	return (1);
}

void	ss(t_node **a, t_node **b)
{
	int	did_a;
	int	did_b;

	did_a = swap_head(a);
	did_b = swap_head(b);
	if (did_a || did_b)
		ft_putstr_fd("ss\n", 1);
}
