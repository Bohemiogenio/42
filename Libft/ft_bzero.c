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

void bzero(void *s, size_t n)
{
    ft_menset(s, 0, n); //“Ve a la dirección s y copia el valor 0 en n bytes seguidos”
}

/* {
   size_t i;
   unsigned char *ptr;

   ptr = (unsigned char *)s;
   i = 0;
   while (i < n)
    {
       ptr[i] = 0;
        i++;
    }
}*/