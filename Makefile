# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/02 03:26:29 by adebray           #+#    #+#              #
#    Updated: 2014/10/02 03:33:59 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: client_lua gfx

re: fclean all

client_lua:
	@echo "#!/bin/sh" > client_lua
	@echo "./bin/love.app/Contents/MacOS/love ./Lua_client" >> client_lua
	chmod 755 client_lua

gfx:
	@echo "#!/bin/sh" > gfx
	@echo "./bin/love.app/Contents/MacOS/love ./GUI" >> gfx
	chmod 755 gfx

clean:
	@echo 'clean called for nothing'

fclean: clean
	rm client_lua
	rm gfx

.PHONY: all clean fclean re
