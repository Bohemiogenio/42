#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h> //para la funcion read
#include <stdlib.h> //para la funciones malloc y free

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32 
#endif

char	*get_next_line(int fd);

#endif
