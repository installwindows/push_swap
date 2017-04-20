# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 14:14:26 by varnaud           #+#    #+#              #
#    Updated: 2017/04/19 22:24:04 by varnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: checker re clean fclean all
CHECKER_NAME=checker

CHECKER_SRC=stack.c \
			main_checker.c \
			operation.c \
			checker.c

CHECKER_OBJ=$(CHECKER_SRC:.c=.o)
CFLAGS=-Wall -Werror -Wextra -g -Ilibft
CC=gcc

$(CHECKER_NAME): $(CHECKER_OBJ)
	$(CC) $(CHECKER_OBJ) -Llibft -lft -o $(CHECKER_NAME)

all: $(CHECKER_NAME) libft.a operation.h stack.h

$(CHECKER_OBJ): checker.h

libft.a:
	make -C libft

clean:
	-make -C libft clean
	-rm -rf $(CHECKER_OBJ)

fclean:
	-make -C libft fclean
	-rm -rf $(CHECKER_NAME)

re: fclean all
