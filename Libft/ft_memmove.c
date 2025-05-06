/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:43:29 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/05/06 15:44:47 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_c;
	size_t				i;
	unsigned char		*dest_c;

	dest_c = (unsigned char *)dest;
	src_c = (const unsigned char *)src;
	if (src_c < dest_c && dest_c < src_c + n)
	{
		while (n--)
			dest_c[n] = src_c[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_c[i] = src_c[i];
			i++;
		}
	}
	return (dest);
}
