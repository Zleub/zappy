map = {}

function map:conf()
	self.address = '*'
	self.port = 4559
	self.cell_size = 32
	self.scale = {2, 2}
	self.timeout = 0.01

	self.tileset = love.graphics.newImage("Images/Tiles0.png")
	self.sprites = love.graphics.newImage("Images/sprites.png")

	self.mapchar = string.byte('M')
	self.charchar = string.byte('C')
	self.celladdchar = string.byte('+')
	self.leavechar = string.byte('L')

	self.characters = {}
	self:load()
end

function map:load()
	self.Quadlist = {
		grass = love.graphics.newQuad(64, 32, self.cell_size, self.cell_size,
					self.tileset:getDimensions()),

		boo = love.graphics.newQuad(127, 6559, self.cell_size, self.cell_size,
					self.sprites:getDimensions()),
		trunk = self:spriteup(12, 1311),
		vegeta = self:spriteup(12, 799)

	}
end

function map:spriteup(sprite_nbr, pixel_row)
	local Quadlist = {}
	local i = 0

	while i ~= sprite_nbr do
		table.insert(Quadlist, love.graphics.newQuad(0 + i * self.cell_size, pixel_row, self.cell_size, self.cell_size,
					self.sprites:getDimensions()))
		i = i + 1
	end
	return Quadlist
end

--
-- String parsing
--

function map.split(str)
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
	if rawcell == '0' then
		return 'Linemate'
	elseif rawcell == '1' then
		return 'Deraumère'
	elseif rawcell == '2' then
		return 'Sibur'
	elseif rawcell == '3' then
		return 'Mendiane'
	elseif rawcell == '4' then
		return 'Phiras'
	elseif rawcell == '5' then
		return 'Thystame'
	elseif rawcell == '6' then
		return 'Nourriture'
	end
end

function map:init_size()
	local tmp = map.split(self.str)

	self.width, self.height = tmp[2], tmp[3]
end

--
-- Read a line form the socket client based on map:conf
--

function map:leave_char()
	local tmp = map.split(self.str)

	for k,v in pairs(self.characters) do
		if v.id == tmp[2] then
			print('Player '..tostring(v.id)..' is dead ...')
			table.remove(self.characters, k)
		end
	end
end

function map:new_char()
	local tmp = map.split(self.str)

	table.insert(self.characters, {
		id = tmp[2],
		x = tmp[3],
		y = tmp[4],
		orientation = tmp[5]
		})
	print(tmp[5])
end

function map:update_cell()
	local tmp = map.split(self.str)

	table.insert(self.data[tmp[2] + 1][tmp[3] + 1].content, map.convert(tmp[4]))
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
			print(
				(i - 1) * self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1] + self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1] + self.cell_size * self.scale[1], (j - 1) * self.cell_size  * self.scale[2] + self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2] + self.cell_size * self.scale[2]
			)
			self.shapes[i][j] = self.HC:addPolygon(
				(i - 1) * self.cell_size, (j - 1) * self.cell_size,
				(i - 1) * self.cell_size + self.cell_size, (j - 1) * self.cell_size,
				(i - 1) * self.cell_size + self.cell_size, (j - 1) * self.cell_size + self.cell_size,
				(i - 1) * self.cell_size, (j - 1) * self.cell_size + self.cell_size
			)
		end
	end
end

function map:getmessage()
	if string.byte(self.str) == self.mapchar then
		self:init_size()
		self:create()
		print("init_size:", self.width, self.height)
	elseif string.byte(self.str) == self.celladdchar then
		self:update_cell()
	elseif string.byte(self.str) == self.charchar then
		self:new_char()
	elseif string.byte(self.str) == self.leavechar then
		self:leave_char()
	else
		-- print(self.str)
	end
end

function map:listen()
	self.str = self.client:receive('*l')

	if self.str ~= nil then
		self:getmessage()
		return 1
	else
		return 0
	end
end

--
-- Handshake to server
--

function map:init()
	love.graphics.setDefaultFilter('nearest')
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

--
-- Love2d's update loop
--


function map:update()
	self.mouse:moveTo(love.mouse.getPosition())
	self:listen()
end

--
-- Love2d's drawing loop
--

function map:draw()
	local x1
	local y1
	local x2
	local y2

	-- love.graphics.scale(self.scale[1], self.scale[2])
	love.graphics.print(love.timer.getFPS(), 550, 300)

	for k,v in pairs(self.shapes) do
		for key,val in pairs(v) do
			x2, y2, x1, y1 = val._polygon:unpack()
			love.graphics.draw(self.tileset, self.Quadlist.grass, x1, y1)
			if self.mouse:collidesWith(val) then
				love.graphics.rectangle("fill", x1, y1, self.cell_size, self.cell_size)
				love.graphics.print(pretty.write(self.data[k][key]), 350, 0)
			end
		end
	end


	for k,char in pairs(self.characters) do
		if char.orientation == '0' then
			love.graphics.draw(self.sprites, self.Quadlist.vegeta[2], char.x * self.cell_size, char.y * self.cell_size)
		elseif char.orientation == '1' then
			love.graphics.draw(self.sprites, self.Quadlist.vegeta[11], char.x * self.cell_size, char.y * self.cell_size)
		elseif char.orientation == '2' then
			love.graphics.draw(self.sprites, self.Quadlist.vegeta[5], char.x * self.cell_size, char.y * self.cell_size)
		elseif char.orientation == '3' then
			love.graphics.draw(self.sprites, self.Quadlist.vegeta[8], char.x * self.cell_size, char.y * self.cell_size)
		end
	end
end

return map
