/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:06:14 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/26 15:06:17 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_node **a)
{
	int	x;
	int	y;
	int	z;

	x = (*a)->val;
	y = (*a)->next->val;
	z = (*a)->next->next->val;
	if (x > y && y < z && x < z)
		sa(a);
	else if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && y < z && x > z)
		ra(a);
	else if (x < y && y > z && x < z)
	{
		sa(a);
		ra(a);
	}
	else if (x < y && y > z && x > z)
		rra(a);
}

static int	pos_min(t_node *a)
{
	int	pos;
	int	i;
	int	min;

	pos = 0;
	i = 0;
	min = INT_MAX;
	while (a)
	{
		if (a->val < min)
		{
			min = a->val;
			pos = i;
		}
		i++;
		a = a->next;
	}
	return (pos);
}

static void	rotate_to_top(t_node **a, int pos)
{
	int	n;
	int	k;

	n = ps_size(*a);
	if (pos <= n / 2)
		while (pos--)
			ra(a);
	else
	{
		k = n - pos;
		while (k--)
			rra(a);
	}
}

static void	push_mins_to_b(t_node **a, t_node **b, int count)
{
	while (count--)
	{
		rotate_to_top(a, pos_min(*a));
		pb(a, b);
	}
}

void	sort_small(t_node **a, t_node **b)
{
	int	n;

	n = ps_size(*a);
	if (n <= 1)
		return ;
	if (n == 2)
	{
		if ((*a)->val > (*a)->next->val)
			sa(a);
		return ;
	}
	if (n == 3)
		return (sort_three(a));
	push_mins_to_b(a, b, n - 3);
	sort_three(a);
	while (*b)
		pa(a, b);
}
