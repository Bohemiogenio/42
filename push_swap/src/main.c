#include "push_swap.h"

static void print_stack(t_node *a)
{
	while(a)
	{
		ft_putnbr_fd(a->val, 1);
		ft_putstr_fd(a->next ? " -> " : "\n", 1);
		a = a->next;
	}
}

int main(void)
{
	t_node *a;

	a = NULL;
	ps_add_back(&a, ps_new(3));
	ps_add_back(&a, ps_new(1));
	ps_add_back(&a, ps_new(2));

	ft_putstr_fd("Inicio A: ", 1);
	print_stack(a);

	/* 1) sa: intercambia 3 y 1 → 1 -> 3 -> 2 */
	ft_putstr_fd("Ejecutando sa...\n", 1);
	sa(&a);
	ft_putstr_fd("A despues de sa: ", 1);
	print_stack(a);

	/* 2) ra: rota hacia arriba → 3 -> 2 -> (1 al final) */
	ft_putstr_fd("Ejecutando ra...\n", 1);
	ra(&a);
	ft_putstr_fd("A despues de ra: ", 1);
	print_stack(a);

	/* 3) rra: rota hacia abajo → el ultimo pasa a principio */
	ft_putstr_fd("Ejecutando rra...\n", 1);
	rra(&a);
	ft_putstr_fd("A despues de rra: ", 1);
	print_stack(a);

	ps_clear(&a);
	return (0);
}

