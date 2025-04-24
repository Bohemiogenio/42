/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:19:21 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/04/22 14:19:44 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "libft.h"

void *ft_memcpy(void *dest , const void *src, size_t n)// Esta función copia 'n' bytes desde 'src' hacia 'dest'.
// Es como clonar datos de un lugar de la memoria a otro.  
    {
        size_t i;                        // Variable para contar cuántos bytes copiamos
        unsigned char *d;               // Creamos un puntero para recorrer 'dest'
        const unsigned char *s;         // Creamos un puntero para recorrer 'src'
    
        // Seguridad: si tanto 'dest' como 'src' son NULL, no podemos hacer nada.
        if (!dest && !src)
            return 0;
    
        // Convertimos los punteros genéricos (void*) a unsigned char* para trabajar byte a byte.
        d = (unsigned char *)dest;
        s = (const unsigned char *)src;
    
        // Empezamos a copiar cada byte, uno por uno, desde 'src' hacia 'dest'
        i = 0;
        while (i < n)
        {
            d[i] = s[i];  // Copia el byte de la posición i
            i++;
        }
    
        // Devolvemos el puntero original al bloque destino (como hace la versión original de memcpy)
        return dest;
    }