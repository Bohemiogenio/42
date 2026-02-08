# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 16:23:34 by raulsanc          #+#    #+#              #
#    Updated: 2026/02/02 14:21:45 by raulsanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c parse.c utils.c init.c destroy.c time.c stop.c print.c routine.c simulation.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

clean:
	rm -f$(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all 
