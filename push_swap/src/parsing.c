/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:05:53 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/26 15:05:55 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	exists_value(t_node *st, int v)
{
	while (st)
	{
		if (st->val == v)
			return (1);
		st = st->next;
	}
	return (0);
}

static int	ps_skip_ws(const char *s, int i)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

static int	ps_read_sign(const char *s, int *i, long *sign)
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

static int	ps_read_number(const char *s, int *i, long sign, int *out)
{
	long	res;

	res = 0;
	while (ft_isdigit(s[*i]))
	{
		res = res * 10 + (s[*i] - '0');
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && -res < INT_MIN))
			return (0);
		(*i)++;
	}
	if (s[*i] && !ft_isspace(s[*i]))
		return (0);
	*out = (int)(res * sign);
	*i = ps_skip_ws(s, *i);
	return (1);
}

static int	parse_one_int(const char *s, int *pos, int *out)
{
	long	sign;
	int		i;

	i = ps_skip_ws(s, *pos);
	if (!s[i])
		return (0);
	if (!ps_read_sign(s, &i, &sign))
		return (0);
	if (!ps_read_number(s, &i, sign, out))
		return (0);
	*pos = i;
	return (1);
}

static int	parse_string_of_ints(const char *s, t_node **a)
{
	int		pos;
	int		value;
	int		found_any;
	t_node	*n;

	pos = 0;
	found_any = 0;
	while (s[pos])
	{
		pos = ps_skip_ws(s, pos);
		if (!s[pos])
			break ;
		if (!parse_one_int(s, &pos, &value))
			return (0);
		if (exists_value(*a, value))
			return (0);
		n = ps_new(value);
		if (!n)
			return (0);
		ps_add_back(a, n);
		found_any = 1;
	}
	return (found_any);
}

int	parse_args(int ac, char **av, t_node **a)
{
	int	i;
	int	ok;

	if (ac < 2)
		return (1);
	ok = 0;
	i = 1;
	while (i < ac)
	{
		if (!parse_string_of_ints(av[i], a))
			return (0);
		ok = 1;
		i++;
	}
	return (ok);
}
