# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/07 21:16:03 by garm              #+#    #+#              #
#    Updated: 2014/10/02 15:51:25 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libftsock.a
LIBS = -lft
FTLIBS = libft.a

SOURCES_DIR = srcs
INCLUDES_DIR = ../../inc

ifeq ($(DEBUG), 1)
	FLAGS = -g -Wall -Wextra -pedantic
	CC = cc
else
	FLAGS = -Wall -Werror -Wextra -ansi -pedantic -std=c89
endif

ifeq ($(STRICT), 1)
	FLAGS += -fstack-protector-all -Wshadow -Wunreachable-code \
			  -Wstack-protector -pedantic-errors -O0 -W -Wundef -fno-common \
			  -Wfatal-errors -Wstrict-prototypes -Wmissing-prototypes \
			  -Wwrite-strings -Wunknown-pragmas -Wdeclaration-after-statement \
			  -Wold-style-definition -Wmissing-field-initializers \
			  -Wpointer-arith -Wnested-externs -Wstrict-overflow=5 -fno-common \
			  -Wno-missing-field-initializers -Wswitch-default -Wswitch-enum \
			  -Wbad-function-cast -Wredundant-decls -fno-omit-frame-pointer \
			  -Wfloat-equal
endif

CFLAGS = $(FLAGS) -I $(INCLUDES_DIR)

DEPENDENCIES = \
			   $(INCLUDES_DIR)/libftsock.h \
			   $(INCLUDES_DIR)/libftsock_struct.h \
			   \

SOURCES = \
			 $(SOURCES_DIR)/ftsock.c \
			 $(SOURCES_DIR)/ftsock_client.c \
			 $(SOURCES_DIR)/ftsock_server.c \
			 $(SOURCES_DIR)/ftsock_resolve.c \
			 $(SOURCES_DIR)/ftsock_error.c \
			 $(SOURCES_DIR)/ftsock_serv_multi_client.c \
			 $(SOURCES_DIR)/ftsock_serv_receive.c \
			 $(SOURCES_DIR)/ftsock_hooks.c \
			 $(SOURCES_DIR)/ftsock_loop.c \
			 $(SOURCES_DIR)/ftsock_serv_send.c \
			 $(SOURCES_DIR)/ftsock_clients_stack.c \
			 $(SOURCES_DIR)/ftsock_serv_close.c \
			 $(SOURCES_DIR)/utils_cbuff_create.c \
			 $(SOURCES_DIR)/utils_cbuff_destroy.c \
			 $(SOURCES_DIR)/utils_cbuff_write.c \
			 $(SOURCES_DIR)/utils_cbuff_bzero.c \

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c $(DEPENDENCIES)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	@echo Creating $(NAME)...
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)
	@echo Deleting $(NAME) OBJECTS files...

fclean: clean
	@rm -f $(NAME)
	@echo Deleting $(NAME)...

re: fclean all

.PHONY: clean fclean re all test

