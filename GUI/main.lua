pretty = require 'pl.pretty'

function love.load()
	map = require 'map':init()
	pretty.dump(map)
end

function love.update(dt)
end

function love.draw()
	map:draw()
end
