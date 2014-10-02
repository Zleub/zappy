function love.load()
	print('Lua_client')
	socket = require 'socket'
	client = socket.connect('*', 4558)

	local str = client:receive()
	print(str)

	client:send('TEAMALPHA\n')
	str = client:receive()
	if str ~= 'ko' then
		print('slots left:', str)
	else
		print('team name undefined')
	end
	str = client:receive()
	print('world size:', str)

	client:send('voir\n')
	str = client:receive()
	print('voir:', str)
end

function love.update(dt)
end

function love.draw()
end
