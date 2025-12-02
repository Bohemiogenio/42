/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:20:47 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/05/14 19:20:56 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_word_size(char const *str, char c, int i)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		size++;
	}
	return (size);
}

static void	ft_free(char **str, int j)
{
	while (j-- > 0)
		free(str[j]);
	free(str);
}

static int	ft_count_letters(char const *s, char c)
{
	int	cont;
	int	word_count;

	cont = 0;
	word_count = 0;
	while (s[cont])
	{
		if (s[cont] != c)
		{
			word_count++;
			while (s[cont] && s[cont] != c)
				cont++;
		}
		else
			cont++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		cont_let;
	int		cont_word;
	int		cont;
	int		word_size;

	cont_let = ft_count_letters(s, c);
	cont = 0;
	str = (char **)malloc(sizeof(char *) * (cont_let + 1));
	cont_word = 0;
	if (!str)
		return (NULL);
	while (cont_word < cont_let)
	{
		while (s[cont] == c)
			cont++;
		word_size = ft_word_size(s, c, cont);
		str[cont_word] = ft_substr(s, cont, word_size);
		if (!str[cont_word])
			return (ft_free(str, cont_word), NULL);
		cont += word_size;
		cont_word++;
	}
	str[cont_word] = NULL;
	return (str);
}
