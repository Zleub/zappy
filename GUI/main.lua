pretty = require 'pl.pretty'

function read(str)
	local tmp = {}

	if str == nil then
		return nil
	end
	for match in string.gmatch(str, "%S+") do
		table.insert(tmp, match);
	end
	return tmp
end

function init_size(str)
	local tmp = read(str)

	if tmp[1] == 'M' then
		return tmp[2], tmp[3]
	else
		return 0, 0
	end
end

function init_cell(str)
	local tmp = read(str)

	if tmp == nil then
		return nil
	elseif tmp[1] == '+' then
		return {x = tmp[2] + 1, y = tmp[3] + 1, c = tmp[4]}
	else
		return nil
	end
end

function insert_cell(map, client)
	local busy = 1
	local rawcell
	while busy == 1 do
		rawcell = init_cell(client:receive('*l'))
		if rawcell == nil then
			break
		else
			table.insert(map[rawcell.x][rawcell.y].content, rawcell.c)
		end
	end
end

function init_map(client, width, height)
	local map = {}
	local cell_nbr = width * height

	for i = 1, width do
		map[i] = {}
		for j = 1, height do
			map[i][j] = {
				x = i - 1,
				y = j - 1,
				content = {}
			}
		end
	end
	return map
end

function love.load()
	socket = require 'socket'
	client = socket.connect('*', 4559)
	client:settimeout(1)

	width, height = init_size(client:receive('*l'))
	map = init_map(client, width, height)
	insert_cell(map, client)

	print(pretty.write(map, "  ", true))
end

function love.update(dt)
end

function draw_map(map, width, height)
	for i = 1, width do
		for j = 1, height do
			love.graphics.rectangle("line", map[i][j].x * 32 + 1, map[i][j].y * 32 + 1, 32, 32)
		end
	end
end

function love.draw()
	draw_map(map, width, height)
end
