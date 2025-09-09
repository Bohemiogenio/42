# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 06:32:46 by raulsanc          #+#    #+#              #
#    Updated: 2025/08/09 06:45:07 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = so_long

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
INCLUDES = -Iinclude -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

SRC = src/main.c src/map_load.c src/map_validate.c src/render.c src/game.c src/map_path.c
OBJ = $(SRC:.c=.o)

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

