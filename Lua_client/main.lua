pretty = require 'pl.pretty'

function love.load()
	print('Lua_client')
	client = require 'client':init()
	-- pretty.dump(client)
	tempo = 0
end

function love.update(dt)
	tempo = tempo + dt
	if tonumber(string.format("%.1f", tempo)) % 1 == 0 then
		client:askInventory()
	end
	client:update()
end

function love.draw()
	client:draw()
end
