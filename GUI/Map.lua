map = {}

function map:conf()
	self.address = '*'
	self.port = 4559
	self.timeout = 3
	self.cell_size = 64
end

function map.read(str)
	local tmp = {}

	if str == nil then
		return nil
	end
	for match in string.gmatch(str, "%S+") do
		table.insert(tmp, match);
	end
	return tmp
end

function map:init_size()
	local tmp = map.read(self.client:receive('*l'))

	if tmp == nil then
		return nil
	elseif tmp[1] == 'M' then
		return tmp[2], tmp[3]
	else
		return 0, 0
	end
end

function map:init_cell()
	local tmp = map.read(self.client:receive('*l'))

	if tmp == nil then
		return nil
	elseif tmp[1] == '+' then
		return { x = tmp[2] + 1, y = tmp[3] + 1, c = tmp[4] }
	else
		return nil
	end
end

function map:insert_cell()
	local busy = 1
	local rawcell

	while busy == 1 do
		rawcell = self:init_cell()
		if rawcell == nil then
			break
		else
			table.insert(self.data[rawcell.x][rawcell.y].content, rawcell.c)
		end
	end
end

function map:create()
	local map = {}
	local cell_nbr = self.width * self.height

	for i = 1, self.width do
		map[i] = {}
		for j = 1, self.height do
			map[i][j] = {
				x = i - 1,
				y = j - 1,
				content = {}
			}
		end
	end
	return map
end

function map:draw()
	for i = 1, self.width do
		for j = 1, self.height do
			love.graphics.rectangle(
				"line",
				self.data[i][j].x * self.cell_size,
				self.data[i][j].y * self.cell_size,
				self.cell_size,
				self.cell_size)
		end
	end
end

function map:init()
	self:conf()
	self.socket = require 'socket'
	self.client = self.socket.connect(self.address, self.port)
	self.client:settimeout(self.timeout)

	self.width, self.height = self:init_size()
	self.data = map:create()
	self:insert_cell()
	return self
end

return map
