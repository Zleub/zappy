map = {}

function map:conf()
	self.address = '*'
	self.port = 4559
	self.cell_size = 32
	self.timeout = 0.01
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

function map.convert(rawcell)
	if rawcell == 0 then
		return 'Nourriture'
	elseif rawcell == 1 then
		return 'Linemate'
	elseif rawcell == 2 then
		return 'Deraumère'
	elseif rawcell == 3 then
		return 'Sibur'
	elseif rawcell == 4 then
		return 'Mendiane'
	elseif rawcell == 5 then
		return 'Phiras'
	elseif rawcell == 6 then
		return 'Thystam'
	end
end

function map:init_size()
	local tmp = map.read(self.client:receive('*l'))

	pretty.dump(tmp)
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
			table.insert(self.data[rawcell.x][rawcell.y].content, map.convert(tonumber(rawcell.c)))
		end
	end
	pretty.dump(self.data)
end

function map:create()
	local data = {}
	local cell_nbr = self.width * self.height
	self.shapes = {}

	for i = 1, self.width do
		data[i] = {}
		self.shapes[i] = {}
		for j = 1, self.height do
			data[i][j] = {
				x = i - 1,
				y = j - 1,
				content = {}
			}
			self.shapes[i][j] = self.HC:addPolygon(
				(i - 1) * self.cell_size, (j - 1) * self.cell_size,
				(i - 1) * self.cell_size + self.cell_size, (j - 1) * self.cell_size,
				(i - 1) * self.cell_size + self.cell_size, (j - 1) * self.cell_size + self.cell_size,
				(i - 1) * self.cell_size, (j - 1) * self.cell_size + self.cell_size
			)
		end
	end
	return data
end

function map:update()
	self.mouse:moveTo(love.mouse.getPosition())
	local str = self.client:receive()
	if str ~= nil then
		print(str)
	end
end

function map:draw()
	for k,v in pairs(self.shapes) do
		for key,val in pairs(v) do
				if self.mouse:collidesWith(val) then
					love.graphics.polygon('fill', val._polygon:unpack())
					love.graphics.print(pretty.write(self.data[k][key]), 350, 0)
				else
					love.graphics.polygon('line', val._polygon:unpack())
				end
		end
	end
end

function map:init()
	self:conf()
	self.socket = require 'socket'
	self.client = self.socket.connect(self.address, self.port)
	self.client:settimeout(self.timeout)

	self.Collider = require 'hardoncollider'
	self.Polygon = require 'hardoncollider.polygon'
	self.HC = self.Collider.new(150)
	self.mouse =  self.HC:addPoint(love.mouse.getPosition())

	print(rectest)

	self.width, self.height = self:init_size()
	self.data = map:create()
	self:insert_cell()
	return self
end

return map
