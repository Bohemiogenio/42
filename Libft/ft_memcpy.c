/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:42:20 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/04/28 11:04:24 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*copy;
	unsigned char	*dest_char;

	copy = (unsigned char *)src;
	dest_char = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		dest_char[i] = copy[i];
		i++;
	}
	return (dest);
}

