#include "push_swap.h"

void	ps_index(t_node *a)
{
	t_node	*i;
	t_node	*j;
	int		count;

	i = a;
	while (i)
	{
		count = 0;
		j = a;
		while (j)
		{
			if (j->val < i->val)
				count++;
			j = j->next;
		}
		i->idx = count;
		i = i->next;
	}
}
