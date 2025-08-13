# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 20:27:43 by raulsanc          #+#    #+#              #
#    Updated: 2025/08/12 20:38:53 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

INCS	= -Iinclude


SRCS	= $(Wilcard src/*.c src/*/*.c)

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME)


%.o %.c include/push_swap.h
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:fclean all


.PHONY: all clean fclean re
