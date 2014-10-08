pretty = require 'pl.pretty'

function love.load()
	print("Loading")
	map = require 'map':init()
	-- pretty.dump(map)
end

function love.update(dt)
	map:update()
end

function love.draw()
	map:draw()
end
