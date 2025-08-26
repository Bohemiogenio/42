/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:06:41 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/22 12:39:31 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_node
{
	int	val; 
	int	idx;
	
	struct s_node *next;
}	t_node;

/*--stack_utils.c--*/
t_node	*ps_new(int val);
t_node	*ps_last(t_node *st);
void	ps_add_back(t_node **st, t_node *n);
int	ps_size(t_node *st);
void	ps_clear(t_node **st);

/*--utils.c--*/
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(const char *s, int fd);
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ps_issorted(t_node *a);

/*--operations_a.c--*/
void	sa(t_node **a);
void	ra(t_node **a);
void	rra(t_node **a);

/*--operations_b.c--*/
void	sb(t_node **b);
void	rb(t_node **b);
void	rrb(t_node **b);

/*--operations_both.c--*/
void	ss(t_node **a, t_node **b);
void	rr(t_node **a, t_node **b);
void	rrr(t_node **a, t_node **b);

/*--operations_push.c--*/
void    pb(t_node **a, t_node **b);
void    pa(t_node **a, t_node **b);

/*--parsing.c--*/
int	parse_args(int ac, char **av, t_node **a);

/*--sort_small.c / sort_big.c--*/
void	sort_small(t_node **a, t_node **b);
void	sort_big(t_node **a, t_node **b);

/*--indexing.c--*/
void	ps_index(t_node *a);

#endif
