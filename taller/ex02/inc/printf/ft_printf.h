/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:50:26 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/17 18:32:25 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(char const *s, ...);
int		ft_fprintf(va_list args, const char f);

int		ft_printnbr(int n);
int		ft_print_ptr(unsigned long long ptr);
char	*ft_uitoa(unsigned int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int num, const char format);

int		ft_putchar(int c);
int		ft_printpercent(void);
int		ft_printstr(char *str);
void	ft_putstr(char *str);
void	ft_put_hex(unsigned int num, const char format);
int		ft_hex_len(unsigned	int num);

char	*ft_itoa(int n);

void	ft_put_ptr(uintptr_t num);
int		ft_ptr_len(uintptr_t num);
int		ft_print_ptr(unsigned long long ptr);

int		ft_num_length(long int n);
char	*ft_itoa(int n);

#endif