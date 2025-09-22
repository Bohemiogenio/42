/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:41:40 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/17 13:04:07 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
		if (str[i] > 'a' && str[i] < 'z')
		{
			if (str[i - 1] < 'a' && str[i - 1] > 'Z')
				str[i] = str[i] - 32;
			if (str[i - 1] < 'A' && str[i - 1] > '9')
				str[i] = str[i] - 32;
			if (str[i - 1] < '0')
				str[i] = str[i] - 32;
			if (str[i - 1] > 'z')
				str[i] = str[i] - 32;
		}
		i++;
	}
	return (str);
}
