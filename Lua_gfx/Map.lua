map = {}

function map:conf()
	self.quiet = 0

	self.address = '*'
	self.port = 4559
	self.cell_size = 32
	self.scale = {2, 2}
	self.timeout = 0.01

	self.tileset = love.graphics.newImage("Images/Tiles0.png")
	self.sprites = love.graphics.newImage("Images/spriteset.png")

	self.mapchar = string.byte('M')
	self.charchar = string.byte('C')
	self.celladdchar = string.byte('+')
	self.celldelchar = string.byte('-')
	self.leavechar = string.byte('L')
	self.lookchar = string.byte('V')
	self.actionchar = string.byte('A')
	self.resultchar = string.byte('R')
	self.inventorychar = string.byte('I')

	self.characters = {}
	self:load()
end

function map:load()
	self.Quadlist = {
		grass = love.graphics.newQuad(64, 32, self.cell_size, self.cell_size,
					self.tileset:getDimensions()),

		-- boo = self:spriteup(12, 6559),
		-- trunk = self:spriteup(12, 1311),
		-- vegeta = self:spriteup(12, 799)

		jack = self:spriteup(12, 0)

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

	print('New Player:')
	print(self.str)
	table.insert(self.characters, {
		id = tmp[2],
		x = tmp[3] * self.scale[1],
		y = tmp[4] * self.scale[2],
		orientation = tmp[5],
		life = tmp[6],
		team = tmp[14]
		})
end

function map:get_char(id)
	for k,v in pairs(self.characters) do
		if v.id == id then
			return v
		end
	end
end

function map:action_char()
	local tmp = map.split(self.str)
	local char = self:get_char(tmp[2])

	if tmp[3] ~= 'A' and tmp[3] ~= 'P' then
		char.orientation = tmp[3]
	end
end

function map:update_inventory()
	local tmp = map.split(self.str)
	local char = self:get_char(tmp[2])

	if tmp[3] == '0' and tmp[4] == '0' and tmp[5] == '0' and
			tmp[6] == '0' and tmp[7] == '0' and tmp[8] == '0' then
		print('Player '..char.id..' takes some food')
	end
end

function map:result_char()
	local tmp = map.split(self.str)
	local char = self:get_char(tmp[2])

	char.x = tmp[3] * self.scale[1]
	char.y = tmp[4] * self.scale[2]
end

function map:look_char()
	local tmp = map.split(self.str)
	local char = self:get_char(tmp[2])

	char.life = tmp[3]
	print('Player '..char.id..' => '..char.life..'/'..'1260'..' looks around')
end

function map:update_cell()
	local tmp = map.split(self.str)

	if tmp[1] == '+' then
		table.insert(self.data[tmp[2] + 1][tmp[3] + 1].content, map.convert(tmp[4]))
	elseif tmp[1] == '-' then
		local ressource = map.convert(tmp[4])

		for k,v in pairs(self.data[tmp[2] + 1][tmp[3] + 1].content) do
			if v == ressource then
				table.remove(self.data[tmp[2] + 1][tmp[3] + 1].content, k)
			end
		end
	end
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
				(i - 1) * self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1] + self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1] + self.cell_size * self.scale[1], (j - 1) * self.cell_size  * self.scale[2] + self.cell_size * self.scale[2],
				(i - 1) * self.cell_size * self.scale[1], (j - 1) * self.cell_size * self.scale[2] + self.cell_size * self.scale[2]
			)
		end
	end
end

function map:getmessage()
	print('GET MSG:', self.str)
	if string.byte(self.str) == self.mapchar then
		self:init_size()
		self:create()
		print("init_size:", self.width, self.height, self.max_health)
	elseif string.byte(self.str) == self.celladdchar then
		self:update_cell()
	elseif string.byte(self.str) == self.celldelchar then
		self:update_cell()
	elseif string.byte(self.str) == self.charchar then
		self:new_char()
	elseif string.byte(self.str) == self.leavechar then
		self:leave_char()
	elseif string.byte(self.str) == self.lookchar then
		self:look_char()
	elseif string.byte(self.str) == self.actionchar then
		-- print('action char', self.str)
		self:action_char()
	elseif string.byte(self.str) == self.resultchar then
		self:result_char()
	elseif string.byte(self.str) == self.inventorychar then
		self:update_inventory()
	else
		print("Not understood message:", self.str)
	end
end

function map:listen()
	self.str = self.client:receive('*l')

	-- print(self.str)

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
	if self.client == nil then
		print('No server @ '..self.address..':'..self.port..'!')
		love.event.quit()
	else
		self.client:settimeout(self.timeout)

		self.Collider = require 'hardoncollider'
		-- self.Polygon = require 'hardoncollider.polygon'
		self.HC = self.Collider.new(150)
		self.mouse =  self.HC:addPoint(love.mouse.getPosition())

		while (42) do
			if self:listen() == 0 then
				break
			end
		end
		return self
	end
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
	local saveup = nil

	-- love.graphics.scale(self.scale[1], self.scale[2])
	local winwidth, winheight = love.window.getDimensions()
	love.graphics.print(love.timer.getFPS(), winwidth - 20, winheight - 20)

	for k,v in pairs(self.shapes) do
		for key,val in pairs(v) do
			x2, y2, x1, y1 = val._polygon:unpack()
			love.graphics.draw(self.tileset, self.Quadlist.grass, x1, y1, 0, self.scale[1], self.scale[2])

			if self.mouse:collidesWith(val) then
				love.graphics.rectangle("line", x1, y1, self.cell_size * self.scale[1], self.cell_size * self.scale[2])


				-- love.graphics.print(pretty.write(self.data[k][key]), 350 * self.scale[1], 0 * self.scale[2])
				saveup = pretty.write(self.data[k][key].content)
-- saveup = pretty.write(self.characters)
				-- love.graphics.setColor(255, 0, 0)
				-- love.graphics.print(pretty.write(self.data[k][key]), mousex + 15, mousey, 0, self.scale[1], self.scale[2])
				-- love.graphics.setColor(255, 255, 255)
			else
			end
		end
	end

	if saveup ~= nil then
		mousex, mousey = love.mouse.getPosition()
		love.graphics.setColor(0, 0, 0)
		love.graphics.print(saveup, mousex + 15, mousey, 0)
		love.graphics.setColor(255, 255, 255)
	end

	for k,char in pairs(self.characters) do
		if char.orientation == '0' then
			love.graphics.draw(
				self.sprites,
				self.Quadlist[char.team][2],
				char.x * self.cell_size,
				char.y * self.cell_size,
				0,
				self.scale[1],
				self.scale[2]
			)
		elseif char.orientation == '1' then
			love.graphics.draw(
				self.sprites,
				self.Quadlist[char.team][11],
				char.x * self.cell_size,
				char.y * self.cell_size,
				0,
				self.scale[1],
				self.scale[2]
			)
		elseif char.orientation == '2' then
			love.graphics.draw(
				self.sprites,
				self.Quadlist[char.team][5],
				char.x * self.cell_size,
				char.y * self.cell_size,
				0,
				self.scale[1],
				self.scale[2]
			)
		elseif char.orientation == '3' then
			love.graphics.draw(
				self.sprites,
				self.Quadlist[char.team][8],
				char.x * self.cell_size,
				char.y * self.cell_size,
				0,
				self.scale[1],
				self.scale[2]
			)
		end
		love.graphics.print(
			char.id,
			char.x * self.cell_size,
			char.y * self.cell_size,
			0,
			self.scale[1] - 1,
			self.scale[2] - 1
		)

		love.graphics.setColor(0, 0, 0)
		love.graphics.rectangle(
			"fill",
			char.x * self.cell_size,
			char.y * self.cell_size + ((self.cell_size - 3) * self.scale[1]),
			(self.cell_size * self.scale[1]),
			2)
		love.graphics.setColor(255, 0, 0)
		love.graphics.rectangle(
			"fill",
			char.x * self.cell_size,
			char.y * self.cell_size + ((self.cell_size - 3) * self.scale[1]),
			(self.cell_size * self.scale[1]) * char.life / 1260,
			2)
		love.graphics.setColor(255, 255, 255)
		love.graphics.rectangle(
			"line",
			char.x * self.cell_size,
			char.y * self.cell_size + ((self.cell_size - 3) * self.scale[1]) - 1,
			(self.cell_size * self.scale[1]),
			2 + 2)


	end
end

return map
