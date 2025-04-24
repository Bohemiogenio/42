#include <stdio.h>
#include "libft.h"
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("\n## isALPHA ##\n");
    printf("%d %d\n", ft_isalpha('A'), isalpha('A'));
    printf("\n## isDIGIT ##\n");
    printf("%d %d\n", ft_isdigit('1'), isdigit('1'));
    printf("\n## isALNUM ##\n");
    printf("%d %d\n", ft_isalnum('A'), isalnum('A'));
    printf("%d %d\n", ft_isalnum('8'), isalnum('8'));
    printf("\n## isASCII ##\n");
    printf("%d %d\n", ft_isascii(65), isascii(65));
    printf("%d %d\n", ft_isascii(200), isascii(200));
    printf("\n## isPRINT ##\n");
    printf("%d %d\n", ft_isprint('A'), isprint('A'));
    printf("%d %d\n", ft_isprint(' '), isprint(' '));
    printf("%d %d\n", ft_isprint(31), isprint(31));
    printf("\n## stLEN ##\n");
    printf("%zu %zu\n", ft_strlen("hola mundo"), strlen("Hola mundo"));
    printf("\n## memSET ##\n");
    char buffer[10];
    ft_memset(buffer, 'X', 5);
    buffer[5] = '\0';
    printf("%s\n", buffer);
    printf("\n## bzero ##\n");   
    ft_bzero(buffer, 10);           
    printf("Después: %s\n", buffer);    
    return 0;
}