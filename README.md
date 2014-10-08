## Zappy

### General Comments

Both client and gfx follow Beone's server protocole as:
- gfx's init build a map and server fill it up ('+' preceded message) 
- character's connexion ('C' preceded message)
- character's death ('L' preceded message)
- character's view order ('V' preceded message, give ticks)
- character's pick up order ('-' preceded message)

### GUI (./gfx)
GUI is a love2d's Lua folder for the gfx exe<br>
modules
- Pl is Penlight by stevedonovan (https://github.com/stevedonovan/Penlight)
- luasocket is sockets for Lua (http://w3.impa.br/~diego/software/luasocket/home.html)
- Map is a module to get a map of a zappy server

files
- Conf.lua is love2d master config

functions
- map:conf is Map module master config
- map.read format string from socket
- map:init_size get size from socket at connexion
- map:init_cell get map data from socket at connexion
- map:insert_cell format map data from socket
- map:create init data table
- map:draw
- map:init init map module

### serv (./serveur)
serv is the C project serveur for zappy
- inc for all libraries includes
- src for all libraries source code
- main.c for code anchor

libs
- libft for C basics
- ft_printf for printf
- curse for ncurses managing style
- libsock for sockets management
- serveur for future serveur lib

