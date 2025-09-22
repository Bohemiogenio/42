/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:06:41 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/21 19:49:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	exists_value(t_node *st, int v)
{
	while (st)
	{
		if (st->val == v)
			return (1);
		st = st->next;
	}
	return (0);
}

int	ps_skip_ws(const char *s, int i)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

int	ps_read_sign(const char *s, int *i, long *sign)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	return (ft_isdigit(s[*i]));
}

int	ps_read_number(const char *s, int *i, long sign, int *out)
{
	long	res;

	res = 0;
	while (ft_isdigit(s[*i]))
	{
		res = res * 10 + (s[*i] - '0');
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && - res < INT_MIN))
			return (0);
		(*i)++;
	}
	if (s[*i] && !ft_isspace(s[*i]))
		return (0);
	*out = (int)(res * sign);
	*i = ps_skip_ws(s, *i);
	return (1);
}
