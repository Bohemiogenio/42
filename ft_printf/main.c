// main.c
#include "ft_printf.h"
#include <stdio.h>


int main(void)
{
    ft_printf("HOLA %s %d %x // ff ADIOS", "Y", 152, 255);
    ft_printf("Hola  mundo!\n");
    ft_printf("Porcentaje: %%\n");
    printf("%d", 23);
	return 0;
}

/*int main ()
{
	int a = 42;
	char *str = "Hello, World!";
	void *ptr = &a;

	ft_printf("Character: %c\n", 'A');
	ft_printf("String: %s\n", str);
	ft_printf("Pointer: %p\n", ptr);
	ft_printf("Decimal: %d\n", a);
ft_printf("Unsigned: %u\n", (unsigned int)a);
	ft_printf("Hexadecimal (lowercase): %x\n", (unsigned int)a);
	ft_printf("Hexadecimal (uppercase): %X\n", (unsigned int)a);
	ft_printf("Percent sign: %%\n");

	return 0;
}
*/