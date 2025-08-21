#include "push_swap.h"

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;

	a = NULL;
	b = NULL;
	if(ac < 2)
		return(0);

	if (!parse_args(ac, av, &a))
	{
		ft_putstr_fd("Error\n", 2);
		ps_clear(&a);
		return (1);
	}
	if (!a || ps_issorted(a))
	{
		ps_clear(&a);
		return (0);
	}
	if (ps_size(a) <= 5)
		sort_small(&a, &b);
	else
		sort_big(&a, &b);
	ps_clear(&a);
	ps_clear(&b);
	return (0);
}
