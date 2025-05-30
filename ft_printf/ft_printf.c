// ft_printf.c
#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;
	char	c;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
			if (format[i] == 'c')
			{
				c = (char)va_arg(args, int);
				write(1, &c, 1);
				count++;
			}
        	else if (format[i] == '%')
        	{	
            	write(1, "%", 1);
            	count++;
        	}
    	}
		else
		{
		write(1, &format[i], 1);
		count++;
		}
		i++;
	}
    va_end(args);
    return count;
}

