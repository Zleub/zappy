client = {}

function client:conf()
	self.address = '*'
	self.port = 4558
	self.timeout = 0.1
	self.team = 'team1\n'
	self.lvl = 1
	self.data = {
		greeting = 'BIENVENUE',
		fail = 'ko',
		death = 'mort'
	}
end

function client.read(str)
	local tmp = {}

	if str == nil then
		return nil
	end
	for match in string.gmatch(str, "%S+") do
		table.insert(tmp, match);
	end
	return tmp
end

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
	tmp = client.read(self.str)
	self.width = tmp[1]
	self.height = tmp[2]
end

function client:send(str) self.client:send(str) end

function client:readline()
	self.str = self.client:receive('*l')
	if self.str == nil then
		print('...')
	else
		-- print(self.str)
	end
end

function client:update()
	self:readline()
	if self.str then
		if self.str == self.data.death then
			love.event.quit()
		end
	end
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

function client:look()
	local tmp

	self:send("voir\n")
	self:readline()
	tmp = client.read(string.sub(self.str, 2, -2))
	print(self.str)
	for k,v in pairs(tmp) do
		print(k,v)
	end
end

function client:getInventory()
	self.str = string.sub(self.str, 2, -2)
	local tmp = client.read(self.str)
	local size = table.getn(tmp)
	local format = {}

	for k,v in pairs(tmp) do
		if k % 2 == 0 and k ~= size then
			format[index] = string.sub(v, 1, -2)
		elseif k % 2 == 0 then
			format[index] = v
		else
			index = v
		end
	end

	return format
end

function client:askInventory()
	self:send("inventaire\n")
	self:readline()
	if self.str ~= nil then
		self.inventory = self:getInventory()
	end
end

function client:printInventory()
	pretty.dump(self.inventory)
end

function client:draw()
	love.graphics.print(
		pretty.write(self.inventory),
		0, 0)
	love.graphics.print(
		pretty.write(self),
		200, 0)
end

function client:init()
	self:conf()
	self.socket = require 'socket'
	self.client = self.socket.connect(self.address, self.port)
	self.client:settimeout(self.timeout)

	self:get_greets()
	self:askInventory()
	self:look()
	-- pretty.dump(self.inventory)
	return self
end

return client
