/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:34:02 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/05 11:39:28 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	if (b != 0)
	{
		*div = a / b;
		*mod = a % b;
	}
}

int main(void)
{
	int	a;
	int	b;
	int	result_div;
	int	result_mod;

	a = 5;
	b = 2;
	result_div = 0;
	result_mod = 0;
	printf("pepito %d mengan %d\n", a, b);
	printf("Before (div, mod): %d, %d\n", result_div, result_mod);
	ft_div_mod(a, b, &result_div, &result_mod);
	printf("After (div, mod): %d, %d", result_div, result_mod);
	return (0);
}
