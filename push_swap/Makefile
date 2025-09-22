# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 20:27:43 by raulsanc          #+#    #+#              #
#    Updated: 2025/08/19 18:03:42 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = push_swap
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCS    = -I include

SRC_DIR = src
OBJ_DIR = obj
SRCS    = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

