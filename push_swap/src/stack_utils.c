/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:06:26 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/26 15:06:28 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ps_new(int val)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->val = val;
	node->idx = -1;
	node->next = NULL;
	return (node);
}

t_node	*ps_last(t_node *st)
{
	if (!st)
		return (NULL);
	while (st->next)
		st = st->next;
	return (st);
}

void	ps_add_back(t_node **st, t_node *n)
{
	t_node	*last;

	if (!st || !n)
		return ;
	if (!*st)
	{
		*st = n;
		return ;
	}
	last = ps_last(*st);
	last->next = n;
}

int	ps_size(t_node *st)
{
	int	count;

	count = 0;
	while (st)
	{
		count++;
		st = st->next;
	}
	return (count);
}

void	ps_clear(t_node **st)
{
	t_node	*tmp;

	if (!st)
		return ;
	while (*st)
	{
		tmp = (*st)->next;
		free(*st);
		*st = tmp;
	}
}
