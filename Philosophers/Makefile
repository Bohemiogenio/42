# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 16:23:34 by raulsanc          #+#    #+#              #
#    Updated: 2026/02/04 14:00:21 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archivos fuente .c
SRCS = main.c parse.c utils.c init.c destroy.c time.c stop.c print.c routine.c \
        simulation.c boss.c forks.c eat.c

# Archivos objeto .o
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -o $(NAME)
	@echo "$(NAME) Compiled successfully"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "Clean completed"

re: fclean all

.PHONY: all clean fclean re 
