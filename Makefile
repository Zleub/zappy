# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/02 03:26:29 by adebray           #+#    #+#              #
#    Updated: 2014/10/31 11:47:36 by Arno             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	serveur
HEADDIR			=	serv/inc
HEADFLAG		=	-I ./$(HEADDIR)

SRCDIR			=	./serv/src
SRC				=	$(SRCDIR)/main.c
OBJ				=	$(subst .c,.o,$(SRC))

CC				=	gcc
CCFLAGS			=	-Werror -Wall -Wextra -Wuninitialized -O3 -g3

LIBLIBFT		=	-L$(SRCDIR)/libft -lft
LIBPRINTF		=	-L$(SRCDIR)/ft_printf -lftprintf
LIBESSENTIAL	=	$(LIBLIBFT) $(LIBPRINTF)

LIBSERVEUR		=	-L$(SRCDIR)/libserv -lserv

LIBNCURSES		=	-L$(SRCDIR)/curse -lcurse
LIBGRAPHIC		=	-lncurses

LIBFLAG			=	$(LIBESSENTIAL) $(LIBNCURSES) $(LIBGRAPHIC) $(LIBSERVEUR)

.PHONY: all clean fclean re $(NAME) client_lua gfx

all: $(NAME) client_lua gfx

makelib: libft printf curse sockets serv

$(NAME): makelib $(OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBFLAG) -o $(NAME) $(OBJ)
	@echo '!'
	@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

libft: $(HEADDIR)/libft.h
	@make -C $(SRCDIR)/libft

printf: $(HEADDIR)/ft_printf.h
	@make -C $(SRCDIR)/ft_printf

curse: $(HEADDIR)/curse.h
	@make -C $(SRCDIR)/curse

sockets: $(HEADDIR)/libftsock.h $(HEADDIR)/libftsock_struct.h
	@make -C $(SRCDIR)/libftsock

serv: $(HEADDIR)/serveur.h
	@make -C $(SRCDIR)/libserv

%.o: %.c $(HEADDIR)/serveur.h
	@echo '.''\c'
	@$(CC) $(CCFLAGS) $(HEADFLAG) -o $@ -c $<

client_lua:
	@echo "#!/bin/sh" > client_lua
	@echo "./bin/love.app/Contents/MacOS/love ./Lua_client" >> client_lua
	chmod 755 client_lua

gfx:
	@echo "#!/bin/sh" > gfx
	@echo "./bin/love.app/Contents/MacOS/love ./GUI" >> gfx
	chmod 755 gfx

clean:
	@make -C $(SRCDIR)/libft clean
	@make -C $(SRCDIR)/curse clean
	@make -C $(SRCDIR)/ft_printf clean
	@make -C $(SRCDIR)/libftsock clean
	@make -C $(SRCDIR)/libserv clean
	@rm -f $(OBJ)
	@echo "\033[31m•\033[0m $(NAME) clean.\033[0m"

fclean: clean
	@make -C $(SRCDIR)/libft fclean
	@make -C $(SRCDIR)/curse fclean
	@make -C $(SRCDIR)/ft_printf fclean
	@make -C $(SRCDIR)/libftsock fclean
	@make -C $(SRCDIR)/libserv fclean
	@rm -f $(OBJ)
	@rm -f $(LIBNAME)
	@rm -f client_lua
	@rm -f gfx
	@rm -f $(NAME)
	@echo "\033[31m•\033[0m $(NAME) fclean: \033[31m$(NAME)\033[0m"

re: fclean all
