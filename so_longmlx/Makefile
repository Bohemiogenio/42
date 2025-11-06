# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 16:20:00 by raulsanc          #+#    #+#              #
#    Updated: 2025/11/06 16:46:18 by Raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude
RM			= rm -f

# Librerías
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

GNL_DIR		= gnl
GNL_LIB		= $(GNL_DIR)/libgnl.a

# Archivos fuente de tu proyecto
SRC_DIR		= src
SRC			= $(SRC_DIR)/main.c
OBJ			= $(SRC:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GNL_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

