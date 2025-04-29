/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:35:07 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/04/28 10:47:24 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
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
