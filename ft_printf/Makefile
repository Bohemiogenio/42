NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c \
      ft_printchar.c \
      ft_printstr.c \
      ft_printptr.c \
      ft_printnbr.c \
      ft_print_unsigned.c \
      ft_printhex.c

OBJ = $(SRC:.c=.o)

AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re