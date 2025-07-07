#include "get_next_line.h"

// Calcula la longitud de una cadena
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// Busca un carácter en una cadena
char	*ft_strchr(const char *s, int character)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)character)
			return ((char *)s + i); // Devuelve un puntero a la primera ocurrencia
		i++;
	}
	if ((char)character == '\0') // Si busca el nulo terminador
		return ((char *)s + i);
	return (NULL);
}

// Rellena un bloque de memoria con ceros
void	ft_bzero(void *str, size_t n)
{
	char	*s;
	size_t	i;

	s = (char *)str;
	i = 0;
	while (i < n)
		s[i++] = '\0';
}

// Asigna memoria e inicializa a cero
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, (count * size));
	return (result);
}

// Une dos cadenas en una nueva memoria asignada
char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2) // Comprobar si alguna de las cadenas de entrada es NULL
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc((len1 + len2 + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		s[len1 + i] = s2[i];
		i++;
	}
	s[len1 + i] = '\0';
	return (s);
}