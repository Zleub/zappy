## Zappy

### GUI
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
