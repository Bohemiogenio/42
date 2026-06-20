/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:27:55 by raulsanc          #+#    #+#             */
/*   Updated: 2026/01/16 16:35:25 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_positive(const char *s)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	if (!s || s[0] == '\0')
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		num = num * 10 + (s[i] - '0');
		if (num > 2147483647)
			return (-1);
		i++;
	}
	return ((int)num);
}
