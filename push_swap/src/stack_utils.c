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

/* Crea un nodo nuevo con el valor dado. idx empieza en -1. */
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

/* Devuelve el último nodo de la lista o NULL si está vacía. */
t_node	*ps_last(t_node *st)
{
	if (!st)
		return (NULL);
	while (st->next)
		st = st->next;
	return (st);
}

/* Añade un nodo al final de la lista. */
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

/* Cuenta los elementos de la lista. */
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

/* Libera por completo la lista y la deja en NULL. */
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
