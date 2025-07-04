#include <fcntl.h> // Para open
#include <unistd.h> // Para read y close
#include <stdio.h>  // Para printf

int main()
{
    int fd;
    char buffer[BUFFER_SIZE + 1]; // +1 para el nulo terminador
    ssize_t bytes_read; // ssize_t es un tipo de dato para el retorno de read

    // Abre un archivo de prueba. Crea uno, por ejemplo "test.txt" con algunas líneas.
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }

    // Lee BUFFER_SIZE bytes del archivo
    bytes_read = read(fd, buffer, BUFFER_SIZE);

    if (bytes_read == -1)
    {
        perror("Error al leer del archivo");
    }
    else
    {
        buffer[bytes_read] = '\0'; // Asegúrate de null-terminar la cadena
        printf("Leído (%zd bytes):\n---\n%s\n---\n", bytes_read, buffer);
    }

    close(fd); // Cierra el archivo
    return (0);
}
