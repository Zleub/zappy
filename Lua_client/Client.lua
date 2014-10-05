client = {}

function client:conf()
	self.address = '*'
	self.port = 4558
	self.timeout = 0.01
	self.team = 'boo\n'
	self.lvl = 1
	self.tencount = 0
	self.centcount = 0
	self.ticks = 1260
	self.data = {
		greeting = 'BIENVENUE',
		fail = 'ko',
		death = 'mort'
	}
	self.view = nil
	self.B_look = 0
	self.B_inv = 0
end

--
-- Object used for look
--

function client.new_viewcell()
	return {
		linemate = 0,
		deraumere = 0,
		sibur = 0,
		mendiane = 0,
		phiras = 0,
		thystame = 0,
		nourriture = 0,
		joueur = 0
	}
end

function client.new_view()
	return {
		client.new_viewcell(),
		client.new_viewcell(),
		client.new_viewcell(),
		client.new_viewcell()
	}
end

--
-- Inherites Functions
--

function client:send(str) self.client:send(str) end

--
-- String parsing
--

function client.split(str)
	local tmp = {}

	if str == nil then
		return nil
	end
	for match in string.gmatch(str, "%S+") do
		table.insert(tmp, match);
	end
	return tmp
end

--
-- Read a line form the socket client based on client:conf
--

function client:readline()
	self.str = self.client:receive('*l')

	if self.str == nil then
		-- print('...')
	elseif self.str == self.data.death then
		print('Ticks: '..self.ticks)
		love.event.quit()
	else
		client:parseline()
	end
end

--
-- Parse a line from the server
--

function client:getInventory(array)
	-- print('getInventory')

	local size = table.getn(array)
	self.inventory = {}

	for k,v in pairs(array) do
		if k % 2 == 0 and k ~= size then
			self.inventory[index] = string.sub(v, 1, -2)
		elseif k % 2 == 0 then
			self.inventory[index] = v
		else
			index = v
		end
	end
	self.B_inv = 0
end

function client:getLook(array)
	local index = 1
	local tmp

	self.view = client.new_view()

	for k,v in pairs(array) do
		if string.byte(v, -1) == string.byte(",") then
			tmp = string.sub(v, 1, -2)
			self.view[index][tmp] = self.view[index][tmp] + 1
			index = index + 1
		else
			self.view[index][v] = self.view[index][v] + 1
		end
	end
	self.B_look = 0
end

function client:parseline()
	local tmp1
	local tmp2

	tmp1 = client.split(string.sub(self.str, 2, -2))
	tmp2 = client.split(self.str)
	if tmp2[2] == nil then
		return
	elseif string.byte(tmp2[2], -1) == string.byte(',') then -- I NEED SOME PARSING REGEXIONS HERE
		self:getInventory(tmp1)
	elseif string.byte(tmp2[1]) == string.byte('{') then -- I NEED SOME PARSING REGEXIONS HERE
		self:getLook(tmp1)
	end
end

--
-- Ask to the client's server
--

function client:askInventory()
	-- print('askInventory')
	if self.B_inv == 0 then
		self:send("inventaire\n")
		self.B_inv = 1
	end
end

function client:askLook()
	-- print('askLook')
	if self.B_look == 0 then
		self:send("voir\n")
		self.B_look = 1
	end
end

--
-- Handshake to server
--

function client:send_team()
	self:send(self.team)
	self:readline()
	if (self.str == self.fail) then
		print('team name undefined')
		love.event.quit()
	else
		self.slots = self.str
	end
end

function client:get_size()
	local tmp

	self:readline()
	tmp = client.split(self.str)
	self.width = tmp[1]
	self.height = tmp[2]
end

function client:get_greets()
	self:readline()
	if (self.str ~= self.data.greeting) then
		print('No welcoming server !')
		love.event.quit()
	end

	self:send_team()
	self:get_size()
end

function client:init()
	self:conf()
	self.socket = require 'socket'
	self.client = self.socket.connect(self.address, self.port)
	self.client:settimeout(self.timeout)

	self:get_greets()
	print('Greets got, lets eat some sayans')
	return self
end

--
-- Love2d's update loop
--

function client:update(dt)
	self.ticks = self.ticks - dt * 100
	self.tencount = self.tencount + dt * 100
	self.centcount = self.centcount + dt * 100

	if self.ticks <= 0 then
		-- You're gonna die
	end
	if self.tencount >= 10 then
		self.tencout = 0
		-- Spawn the server
	end
	if self.centcount >= 100 then
		self.centcount = 0
		self:askLook()
		-- self:askInventory()
	end
	self:readline()
	self.str = nil
end

--
-- Love2d's drawing loop
--

function client:draw()
	love.graphics.print(
		pretty.write(self.inventory), 0, 0)
	love.graphics.print(love.timer.getFPS(), 200, 0)
	if self.tencount >= 10 then
		love.graphics.print(pretty.write(self.view), 200, 12)
	end
end

return client
