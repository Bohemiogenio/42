/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:18:24 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/07/01 17:18:28 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_format(va_list args, const char format);
int	ft_printchar(char c);
int	ft_printstr(char *s);
int	ft_printptr(void *ptr);
int	ft_printnbr(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_printhex(unsigned int n, char format);

#endif
