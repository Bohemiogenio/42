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

void	*ft_memmove(void *s1, const void *s2, size_t len)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned int	i;

	dst = (unsigned char *)s1;
	src = (unsigned char *)s2;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (0 < len--)
			dst[len] = src[len];
	}
	return (dst);
}
