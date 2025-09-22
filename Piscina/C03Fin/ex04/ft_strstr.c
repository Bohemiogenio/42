/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:36:25 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/18 13:37:26 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strstr(char *str, char *to_find)
{
	char	*s;
	char	*f;

	if (*to_find == '\0')
		return (str);
	while (*str != '\0')
	{
		if (*str == *to_find)
		{
			s = str;
			f = to_find;
			while (*s == *f && *f != '\0')
			{
				s++;
				f++;
			}
			if (*f == '\0')
				return (str);
		}
		str++;
	}
	return (NULL);
}
