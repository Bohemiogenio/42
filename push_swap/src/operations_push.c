/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:45 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/26 15:05:47 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_node **from, t_node **to, const char *op)
{
	t_node	*tmp;

	if (!from || !*from || !to)
		return ;
	tmp = *from;
	*from = (*from)->next;
	tmp->next = *to;
	*to = tmp;
	ft_putstr_fd(op, 1);
}

void	pb(t_node **a, t_node **b)
{
	push(a, b, "pb\n");
}

void	pa(t_node **a, t_node **b)
{
	push(b, a, "pa\n");
}
