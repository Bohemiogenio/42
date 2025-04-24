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

void *ft_memset(void *b, int c, size_t len)
{
    size_t      i;
    unigned char *ptr;
    i = 0;
    ptr = (unsigned char *)b;

    while (i < len)
    ptr[i++] = (unsigned char)c;
    return (b);
}