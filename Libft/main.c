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
    printf("\n## memCPY ##\n");
    char src_copy[] = "abcdef";
    char dest_copy[10];
    ft_memcpy(dest_copy, src_copy, 6);
    printf("%s\n", dest_copy);
    printf("\n## memMOVE ##\n");
    char overlap[] = "123456";
    ft_memmove(overlap + 2, overlap, 4); // Solapamiento
    printf("%s\n", overlap);
    printf("\n## strLCPY ##\n");
    char dst1[20];
    char *src1 = "Hello";
    printf("%zu\n", ft_strlcpy(dst1, src1, sizeof(dst1)));
    printf("Resultado: %s\n", dst1);
    printf("\n## strLCAT ##\n");
    char dst2[20] = "Hola";
    char *src2 = " Mundo";
    printf("%zu\n", ft_strlcat(dst2, src2, sizeof(dst2)));
    printf("Resultado: %s\n", dst2);
    printf("\n## toUPPER y toLOWER ##\n");
    printf("%d %d\n", ft_toupper('b'), toupper('b'));
    printf("%d %d\n", ft_tolower('G'), tolower('G'));
    printf("\n## strCHR ##\n");
    printf("%s\n", ft_strchr("Hola mundo", 'm'));
    printf("\n## strRCHR ##\n");
    printf("%s\n", ft_strrchr("Hola mundo", 'o'));
    printf("\n## strNCMP ##\n");
    printf("%d\n", ft_strncmp("Hola", "Holc", 4));
    printf("\n## memCHR ##\n");
    char mem[] = "abcdef";
    printf("%s\n", (char *)ft_memchr(mem, 'd', 6));
    printf("\n## memCMP ##\n");
    printf("%d\n", ft_memcmp("abcde", "abcdf", 5));
    printf("\n## strNSTR ##\n");
    printf("%s\n", ft_strnstr("Hola mundo", "mun", 10));
    printf("\n## ATOI ##\n");
    printf("%d\n", ft_atoi("   -1234"));
    printf("\n## CALLOC ##\n");
    int *arr = (int *)ft_calloc(4, sizeof(int));
    if (arr)
    {
        for (int i = 0; i < 4; i++)
            printf("%d ", arr[i]);
        printf("\n");
        free(arr);
    }
    printf("\n## STRDUP ##\n");
    char *original = "libft";
    char *copy = ft_strdup(original);
    printf("Original: %s\nDuplicado: %s\n", original, copy);
    free(copy);
    return 0;
}