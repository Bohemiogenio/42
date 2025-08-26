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
	{
		while (pos--)
			ra(a);
	}
	else
	{
		k = n - pos;
		while (k--)
			rra(a);
	}
}

void	sort_small(t_node **a, t_node **b)
{
	int	n;
	int	pushes;
	int	p;

	n = ps_size(*a);
	if (n <= 1)
		return ;
	if (n == 2 && (*a)->val > (*a)->next->val)
	{
		sa(a);
		return ;
	}
	if (n == 3)
	{
		sort_three(a);
		return ;
	}
	pushes = n - 3;
	while (pushes--)
	{
		p = pos_min(*a);
		rotate_to_top(a, p);
		pb(a, b);
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}
