# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 14:14:26 by varnaud           #+#    #+#              #
#    Updated: 2017/05/21 18:21:15 by varnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: checker push_swap re clean fclean all

PUSHSWAP_NAME=push_swap
CHECKER_NAME=checker

CHECKER_SRC=stack.c \
			main_checker.c \
			operation.c \
			checker.c \
			utils.c \
			parse_argument.c \
			parse_number.c

PUSHSWAP_SRC=main_pushswap.c \
			utils.c \
			operation.c \
			stack.c \
			pushswap.c \
			parse_argument.c \
			parse_number.c \
			sort_5.c \
			sort_x.c

CHECKER_OBJ=$(CHECKER_SRC:.c=.o)
PUSHSWAP_OBJ=$(PUSHSWAP_SRC:.c=.o)
CFLAGS=-Wall -Wextra -g -Ilibft
CC=gcc

all: $(CHECKER_NAME) $(PUSHSWAP_NAME) operation.h stack.h utils.h

$(CHECKER_NAME): $(CHECKER_OBJ) libft.a
	$(CC) $(CHECKER_OBJ) -Llibft -lft -o $(CHECKER_NAME)

$(PUSHSWAP_NAME): $(PUSHSWAP_OBJ) libft.a
	$(CC) $(PUSHSWAP_OBJ) -Llibft -lft -o $(PUSHSWAP_NAME)

$(CHECKER_OBJ): checker.h

$(PUSHSWAP_OBJ): pushswap.h

libft.a:
	make -C libft

clean:
	-make -C libft clean
	-rm -rf $(CHECKER_OBJ) $(PUSHSWAP_OBJ)

fclean: clean
	-make -C libft fclean
	-rm -rf $(CHECKER_NAME) $(PUSHSWAP_NAME)

re: fclean all
