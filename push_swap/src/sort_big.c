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

void	sort_big(t_node **a, t_node **b)
{
	int		max_bits;
	int		i;
	int		j;
	int		n;

	/* 1) asignar idx 0..n-1 */
	ps_index(*a);

	/* ===== DEBUG (temporal): ver idx asignados y max_bits ===== */
	{
		t_node	*t;

		t = *a;
		ft_putstr_fd("IDX: ", 1);
		while (t)
		{
			ft_putnbr_fd(t->idx, 1);
			ft_putstr_fd(" ", 1);
			t = t->next;
		}
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("BITS: ", 1);
		ft_putnbr_fd(get_max_bits(*a), 1);
		ft_putstr_fd("\n", 1);
	}
	/* ===== /DEBUG ===== */

	/* 2) nº de pasadas (bits) */
	max_bits = get_max_bits(*a);

	/* 3) radix LSD por bits: 0 -> B (pb), 1 -> rota en A (ra), luego pa */
	i = 0;
	while (i < max_bits)
	{
		n = ps_size(*a);
		j = 0;
		while (j < n)
		{
			if ((((*a)->idx >> i) & 1) == 1)
				ra(a);           /* bit=1 → rota en A */
			else
				pb(a, b);        /* bit=0 → empuja a B */
			j++;
		}
		while (*b)
			pa(a, b);            /* devolver todo a A */
		i++;
	}
}
