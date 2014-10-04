map = {}

function map:conf()
	self.address = '*'
	self.port = 4559
	self.cell_size = 32
	self.timeout = 0.01

	self.mapchar = string.byte('M')
	self.charchar = string.byte('C')
	self.celladdchar = string.byte('+')
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
	local tmp = map.read(self.str)

	self.width, self.height = tmp[2], tmp[3]
end

function map:create()
	local cell_nbr = self.width * self.height
	self.data = {}
	self.shapes = {}

	for i = 1, self.width do
		self.data[i] = {}
		self.shapes[i] = {}
		for j = 1, self.height do
			self.data[i][j] = {
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

function map:update_cell()
	local tmp = map.read(self.str)

	table.insert(self.data[tmp[2] + 1][tmp[3] + 1].content, map.convert(tonumber(tmp[4])))
end

function map:getmessage()
	-- print(self.str)
	if string.byte(self.str) == self.mapchar then
		self:init_size()
		self:create()
		print("init_size:", self.width, self.height)
	elseif string.byte(self.str) == self.celladdchar then
		self:update_cell()
	elseif string.byte(self.str) == self.charchar then
		print(str)
	end
end

function map:listen()
	self.str = self.client:receive('*l')
	-- print(self.str)
	if self.str ~= nil then
		self:getmessage()
		-- print(self.str)
		return 1
	else
		print("listen ...")
		return 0
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

	while (42) do
		if self:listen() == 0 then
			break
		end
	end
	return self
end

return map
