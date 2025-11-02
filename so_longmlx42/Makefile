# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 14:16:03 by raulsanc          #+#    #+#              #
#    Updated: 2025/11/02 14:16:13 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I include -I $(MLX42_DIR)/include
LDFLAGS	= $(MLX42_DIR)/build/libmlx42.a -lglfw -ldl -lm -pthread

MLX42_DIR	= MLX42

SRC_DIR	= src
OBJ_DIR	= obj

SRC	= $(SRC_DIR)/main.c \
	$(SRC_DIR)/hooks.c \
	$(SRC_DIR)/cleanup.c

OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "\033[32m[OK]\033[0m Built $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[33m[CC]\033[0m $<"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
