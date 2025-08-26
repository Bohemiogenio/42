/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:57:03 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/22 12:57:05 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_node *a)
{
	int		max_idx;
	int		bits;
	t_node	*tmp;

	max_idx = 0;
	tmp = a;
	while (tmp)
	{
		if (tmp->idx > max_idx)
			max_idx = tmp->idx;
		tmp = tmp->next;
	}
	bits = 0;
	while ((max_idx >> bits) != 0)
		bits++;
	return (bits);
}

static void	pass_bit(t_node **a, t_node **b, int bit)
{
	int	n;
	int	j;

	n = ps_size(*a);
	j = 0;
	while (j < n)
	{
		if ((((*a)->idx >> bit) & 1) == 1)
			ra(a);
		else
			pb(a, b);
		j++;
	}
}

void	sort_big(t_node **a, t_node **b)
{
	int	max_bits;
	int	i;

	ps_index(*a);
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		pass_bit(a, b, i);
		while (*b)
			pa(a, b);
		i++;
	}
}
