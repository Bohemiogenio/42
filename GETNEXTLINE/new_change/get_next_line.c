#include "get_next_line.h"

// Une dos cadenas y libera la primera
char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2); // Usa el ft_strjoin renombrado
	if (s1)
		free(s1); // Libera el primer string después de la unión
	return (new_str);
}

// Extrae la parte de la 'stash' que NO es la línea actual
char	*the_rest(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0') // Si no hay salto de línea, todo se ha procesado
	{
		free(stash);
		return (NULL);
	}
	// Si hay salto de línea, la nueva stash comienza después de este
	i++; // Moverse más allá del '\n'
	new_stash = ft_calloc(1, ft_strlen(stash + i) + 1); // Asignar memoria para el resto
	if (!new_stash)
	{
		free(stash); // Liberar la stash antigua si la nueva asignación falla
		return (NULL);
	}
	j = 0;
	while (stash[i] != '\0')
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash); // Liberar la stash antigua
	return (new_stash);
}

// Extrae la línea actual de la 'stash'
char	*make_line_from(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || stash[0] == '\0') // Si la stash es NULL o está vacía
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	// Asignar memoria para la línea, incluyendo '\n' si existe y el '\0'
	line = ft_calloc(1, (i + (stash[i] == '\n' ? 1 : 0) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n'; // Incluir el salto de línea y avanzar el índice
	line[i] = '\0'; // Terminar la línea con nulo
	return (line);
}

// Lee del file descriptor hasta encontrar un salto de línea o EOF
char	*read_until_enter(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;

	// Si stash es NULL al inicio, se inicializa como una cadena vacía
	if (!stash)
		stash = ft_calloc(1, 1);
	if (!stash) // Comprobar si la asignación inicial de stash falló
		return (NULL);

	buffer = ft_calloc(1, BUFFER_SIZE + 1); // Asignar buffer temporal
	if (!buffer)
	{
		free(stash); // Liberar stash si la asignación de buffer falla
		return (NULL);
	}
	bytes_read = 1; // Inicializar para entrar al bucle
	// Leer hasta encontrar un salto de línea en stash o hasta EOF/error
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) // Error de lectura
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0'; // Asegurar que el buffer esté terminado en nulo
		stash = ft_free_strjoin(stash, buffer); // Unir lo leído a stash y liberar la stash antigua
		if (!stash) // Comprobar si ft_free_strjoin falló
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer); // Liberar el buffer temporal
	return (stash);
}

// Función principal: lee una línea de un file descriptor
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash; // 'stash' para guardar el resto de la lectura entre llamadas

	// Comprobaciones iniciales de fd, BUFFER_SIZE y si el fd es legible
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash) // Si hay algo en stash, liberarlo en caso de FD inválido
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}

	stash = read_until_enter(fd, stash); // Lee del FD y actualiza la stash
	if (!stash) // Si read_until_enter falla o no hay nada que leer
		return (NULL);

	line = make_line_from(stash); // Extrae la línea de la stash
	if (!line) // Si no se pudo formar una línea (ej. stash vacía después de lectura)
	{
		free(stash); // Liberar la stash si no se extrajo ninguna línea
		stash = NULL;
		return (NULL);
	}

	stash = the_rest(stash); // Actualiza la stash con el contenido restante

	return (line);
}