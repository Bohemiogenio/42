NAME=libftprintf.a
AR=ar rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

FILES = ft_printf.c \
		ft_printf_num.c \
		ft_printf_ptr.c \
		ft_printf_utils.c \
		ft_printf_itoa.c \
		ft_printf_str.c

OBJS=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $?

%.o: %.c
	cc -c $(CFLAGS) $?

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re