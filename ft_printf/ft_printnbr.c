#include "ft_printf.h"

int	ft_printnbr(int n)
{
	long	num;
	int		count;
	char	digit;

	num = n;
	count = 0;
	if (num < 0)
	{
		write(1, "-", 1);
		count++;
		num = -num;
	}
	if (num > 9)
		count += ft_printnbr(num / 10);
	digit = (num % 10) + '0';
	write(1, &digit, 1);
	count++;
	return (count);
}