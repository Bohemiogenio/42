#include "push_swap.h"

static int	exists_value(t_node *st, int v)
{
	while(st)
	{
		if(st->val == v)
			return (1);
		st = st->next;
	}
	return (0);
}

static int	parse_one_int(const char *s, int *pos, int *out)
{
	long	sign;
	long	res;
	int	i;

	i = *pos;
	while(s[i] && ft_isspace(s[i]))
		i++;
	if(!s[i])
		return (0);
	sign = 1;
	if(s[i] == '+' || s[i] == '-')
	{
		if(s[i] == '-')
			sign = -1;
		i++;
	}
	if(!ft_isdigit(s[i]))
		return (0);
	res = 0;
	while(ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		if(sign == 1 && res > INT_MAX)
			return (0);
		if(sign == -1 && -res < INT_MIN)
			return (0);
		i++;
	}
	if(s[i] && !ft_isspace(s[i]))
		return (0);
	*out = (int)(res * sign);
	while(s[i] && ft_isspace(s[i]))
		i++;
	*pos = i;
	return (1);
}

static int	parse_string_of_ints(const char *s, t_node **a)
{
	int pos;
	int value;
	int found_any;

	pos = 0;
	found_any = 0;
	while(s[pos])
	{
		while(s[pos] && ft_isspace(s[pos]))
			pos++;
		if(!s[pos])
			break;
		if(!parse_one_int(s, &pos, &value))
			return (0);
		if(exists_value(*a, value))
			return (0);
		ps_add_back(a, ps_new(value));
		if(!ps_last(*a))
			return (0);
		found_any = 1;
	}
	return (found_any);
}

int	parse_args(int ac, char **av, t_node **a)
{
	int i;
	int ok_one;

	if(ac > 2)
		return(1);
	i = 1;
	ok_one = 0;
	while(i < ac)
	{
		if(!parse_string_of_ints(av[i], a))
			return (0);
		ok_one = 1;
		i++;
	}
	return (ok_one);
}
