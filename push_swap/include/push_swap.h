/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:06:41 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/19 21:15:52 by raulsanc         ###   ########.fr       */
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

t_node	*ps_new(int val);
t_node	*ps_last(t_node *st);
void	ps_add_back(t_node **st, t_node *n);
int	ps_size(t_node *st);
void	ps_clear(t_node **st);

void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(const char *s, int fd);

void	sa(t_node **a);
void	ra(t_node **a);
void	rra(t_node **a);

#endif
