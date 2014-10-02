client = {}

function client:conf()
	self.address = '*'
	self.port = 4558
	self.timeout = 0.1
	self.team = 'team1\n'
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
		print(self.str)
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

function client:getInventory()

end

function client:look()
	self:send("voir\n")
	self:readline()
	self.inventory = self:getInventory()
end

function client:init()
	self:conf()
	self.socket = require 'socket'
	self.client = self.socket.connect(self.address, self.port)
	self.client:settimeout(self.timeout)

	self:get_greets()
	self:look()
	return self
end

return client
