pretty = require 'pl.pretty'

function love.load()
	print('Lua_client')
	client = require 'client':init()
	-- pretty.dump(client)
end

function love.update(dt)
	client:update(dt)
end

function love.draw()
	client:draw()
end
