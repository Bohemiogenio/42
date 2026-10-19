/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 libft.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: Raulsanc <raulsanc@student.42malaga.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/04/28 09:48:27 by Raulsanc		   #+#	  #+#			  */
/*	 Updated: 2026/09/16 11:59:18 by mmorente		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h> // For malloc, free, etc.

// Libft functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

// Printf functions
int		ft_printf(char const *str, ...);
int		ft_printstr(const char *str, int counter);
int		ft_printnb(int n, int counter);
int		ft_putchar(char c);
int		ft_print_uns_numb(unsigned int nb, int counter);
int		ft_print_ptr(unsigned long long mem_dir);
int		ft_print_hex(unsigned long long num_hex);
int		ft_print_hex_may(unsigned long long num_hex);

// GetNextLine functions
char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen_gnl(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char *str, int c);

#endif
