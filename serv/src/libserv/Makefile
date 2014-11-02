# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/31 11:23:14 by Arno              #+#    #+#              #
#    Updated: 2014/11/02 19:43:50 by Arno             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libserv.a
LIB			=	serv
HEADDIR		=	 ../../inc

SRC			=	env.c \
				client.c \
				client_list.c \
				sock.c \
				team.c

OBJ			= $(subst .c,.o,$(SRC))

CC			= gcc
CCFLAGS		= -Werror -Wall -Wextra -Wuninitialized -O3 -g

all: $(NAME)

$(NAME):	$(OBJ)
			@ar rc $@ $^
			@ranlib $@
			@echo '!'
			@echo "\033[32m•\033[0m Libft compil: \033[32m$(NAME)\033[0m"

%.o:		%.c
			@echo '.''\c'
			@$(CC) $(CCFLAGS) -I $(HEADDIR) -o $@ -c $<

clean:
			@rm -f $(OBJ)
			@echo "\033[31m•\033[0m libft clean.\033[0m"

fclean:		clean
			@rm -f $(NAME)
			@echo "\033[31m•\033[0m libft fclean: \033[31m$(NAME)\033[0m"

re:			fclean all

.PHONY: all clean fclean re
