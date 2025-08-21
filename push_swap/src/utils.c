#include "push_swap.h"

void	ft_putstr_fd(const char *s, int fd)
{
	int i;

	if(!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*Imprime un entero en fd(sirve para debug)*/
void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;
	
	nb = n;
	if(nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if(nb > 9)
		ft_putnbr_fd((int)(nb / 10), fd);
	c = (char)('0' + (nb % 10));
	write(fd, &c, 1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	ps_issorted(t_node *a)
{
	while (a && a->next)
	{
		if(a->val > a->next->val)
			return (0);
		a = a->next;
	}
	return (1);
}
