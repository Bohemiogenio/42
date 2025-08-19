#include "push_swap.h"
/*Crea un nodo nuevo con un valor */
t_node *ps_new(int val)
{
	t_node	*node;
	
	node = (t_node *)malloc(sizeof(t_node));
	if(!node)
		return (NULL);
	node->val = val;
	node->idx = -1;
	node->next = NULL;
	return (node);
}
/* Devuelve el ultimo nodo de la lista o NULL si vacia*/
t_node *ps_last(t_node *st)
{
	while(st && st->next)
		st = st->next;
	return (st);
}
/* Añade un nodo al final de la lista*/
void	ps_add_back(t_node **st, t_node *n)
{
	t_node *last;
	
	if(!st || !n)
		return ;
	if(!*st)
	{
		*st = n;
		return ;
	}
	last = ps_last(*st);
	last->next = n;
}
/*Cuenta elementos de la lista */
int	ps_size(t_node *st)
{
	int count;

	count = 0;
	while(st)
	{
		count++;
		st = st->next;
	}
	return (count);
}
/*Liberar toda la lista*/
void	ps_clear(t_node **st)
{

	t_node *tmp;
	
	if(!st)
		return ;
	while(*st)
	{
		tmp = (*st)->next;
		free(*st);
		*st = tmp;
	}
}
