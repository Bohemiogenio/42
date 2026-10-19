# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorente <mmorente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:06:42 by mmorente          #+#    #+#              #
#    Updated: 2026/10/08 19:21:53 by martinmv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

OBJ_DIR = obj

SRCS = $(shell find src -name '*.c' | sort -u) \

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

CC     = cc
CFLAGS = -Wall -Wextra -Werror -g -std=gnu17

MLX42_PATH  = libs/minilibx-linux
LIBFT_PATH  = libs/libft

MLX42  = $(MLX42_PATH)/libmlx_Linux.a
LIBFT  = $(LIBFT_PATH)/libft.a

HEADERS = -I. -Isrc -Ilibs/mlx_linux -Ilibs/libft

all: $(NAME)

$(NAME): $(OBJ) $(MLX42) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(LIBFT) \
		$(HEADERS) -L$(MLX42_PATH) -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(MLX42):
	make -C $(MLX42_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX42_PATH) clean

re: fclean all

.PHONY: all clean fclean re
