/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:19 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/22 23:59:59 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rotate_up(t_node **s)
{
	t_node	*first;
	t_node	*last;

	if (!s || !*s || !(*s)->next)
		return (0);
	first = *s;
	last = ps_last(*s);
	*s = first->next;
	first->next = NULL;
	last->next = first;
	return (1);
}

static int	rotate_down(t_node **s)
{
	t_node	*prev;
	t_node	*last;

	if (!s || !*s || !(*s)->next)
		return (0);
	prev = NULL;
	last = *s;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *s;
	*s = last;
	return (1);
}

void	rr(t_node **a, t_node **b)
{
	int	did_a;
	int	did_b;

	did_a = rotate_up(a);
	did_b = rotate_up(b);
	if (did_a || did_b)
		ft_putstr_fd("rr\n", 1);
}

void	rrr(t_node **a, t_node **b)
{
	int	did_a;
	int	did_b;

	did_a = rotate_down(a);
	did_b = rotate_down(b);
	if (did_a || did_b)
		ft_putstr_fd("rrr\n", 1);
}
