# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 16:20:00 by raulsanc          #+#    #+#              #
#    Updated: 2025/12/02 21:10:00 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

# ==== DIRECTORIOS ====
SRC_DIR		= src
INC_DIR		= include
LIBFT_DIR	= libft
GNL_DIR		= gnl
MLX_DIR		= MLX42

# ==== LIBRERÍAS ====
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
GNL_LIB		= $(GNL_DIR)/libgnl.a
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a

# ==== FLAGS ====
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)/include
MLX_FLAGS	= $(MLX_LIB) -ldl -lglfw -pthread -lm

# ==== FUENTES ====
SRC         = $(SRC_DIR)/main.c \
              $(SRC_DIR)/ber_check.c \
              $(SRC_DIR)/load_map.c \
              $(SRC_DIR)/validate_rect.c \
              $(SRC_DIR)/validate_charset.c \
              $(SRC_DIR)/validate_walls.c \
              $(SRC_DIR)/validate_path.c \
              $(SRC_DIR)/validate_path_utils.c \
              $(SRC_DIR)/init_mlx42.c \
              $(SRC_DIR)/render_sprites.c \
              $(SRC_DIR)/player_input.c \
              $(SRC_DIR)/utils.c

OBJ			= $(SRC:.c=.o)

# ==== REGLAS ====

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GNL_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

# ==== UTILS ====
mlx:
	cmake -B $(MLX_DIR)/build -S $(MLX_DIR)
	cmake --build $(MLX_DIR)/build -j

run: all
	./$(NAME) maps/ok.ber

norm:
	norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re mlx run norm