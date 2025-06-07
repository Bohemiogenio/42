#include "ft_printf.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}