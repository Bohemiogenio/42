# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 16:27:43 by Raulsanc          #+#    #+#              #
#    Updated: 2025/11/06 16:28:39 by Raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libgnl.a
SRC		= get_next_line.c get_next_line_utils.c
OBJ		= $(SRC:.c=.o)
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

