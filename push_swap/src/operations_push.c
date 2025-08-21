#include "push_swap.h"

static void push(t_node **from, t_node **to, const char *op)
{
	t_node *tmp;

	if(!from || !*from)
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
