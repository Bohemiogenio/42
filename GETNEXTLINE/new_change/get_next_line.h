#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 /* Tamaño por defecto del buffer si no se define en la compilación */
# endif

# include <unistd.h> /* Para la función read() */
# include <stdlib.h> /* Para las funciones malloc() y free() */

/* Funciones de utilidad (de get_next_line_utils.c)*/
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char *s1, char *s2); /* Renombrada de ft_strcat */

/* Funciones auxiliares específicas de GNL (de get_next_line.c)*/
char				*ft_free_strjoin(char *s1, char *s2); /*  Auxiliar para unir y liberar el primer string */
char				*the_rest(char *stash); /* Obtiene el resto de la 'stash' después de la línea */
char				*make_line_from(char *stash); /* Extrae la línea de la 'stash' */
char				*read_until_enter(int fd, char *stash); /* Lee del fd hasta encontrar un salto de línea */

/* Funcion Principal */
char				*get_next_line(int fd);

#endif