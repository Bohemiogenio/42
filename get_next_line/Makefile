NAME = get_next_line
CC = cc
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42 # Ejemplo, luego GNL lo toma del .h si no se pasa por parametro
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main.c -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
