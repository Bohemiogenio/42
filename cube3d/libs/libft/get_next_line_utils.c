/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:35:33 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:34:33 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*endstr;
	size_t		totlen;
	int			i;
	int			j;

	totlen = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	endstr = ft_calloc(sizeof(char), (totlen + 1));
	if (!endstr)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		endstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		endstr[i++] = s2[j++];
	free(s1);
	return (endstr);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			i;
	size_t			n;

	n = size * nmemb;
	p = malloc(n);
	if (!p)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*buff_src;
	unsigned char	*buff_dest;

	buff_src = (unsigned char *)src;
	buff_dest = (unsigned char *)dest;
	while (n > 0)
	{
		*buff_dest = buff_src[0];
		buff_src++;
		buff_dest++;
		n--;
	}
	return (dest);
}
