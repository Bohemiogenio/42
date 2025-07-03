#include "ft_printf.h"
#include <stdio.h>


int main(void)
{
	ft_printf("Char: %c\n", 'A');
	ft_printf("String: %s\n", "Hola mundo");
	ft_printf("Pointer: %p\n", (void *)"c");
	ft_printf("Decimal: %d\n", -42);
	ft_printf("Integer: %i\n", 1337);
	ft_printf("Unsigned: %u\n", 389898);
	ft_printf("Hex lower: %x\n", 255);
	ft_printf("Hex upper: %X\n", 255);
	ft_printf("Porcentaje: %%\n");
	ft_printf("Hola %s tiene %d años", "Juan", 25);
	return (0);
}
