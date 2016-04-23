local Config = require 'Config'
local Logger = require 'Logger'

local Context = {}
Context.__index = Context

function Context:new()
    ctx = context.init()
    Config = Config:new(ctx)
    Logger = Logger:new(ctx)

    return setmetatable({
        ctx = ctx,
        Config = Config,
        Logger = Logger
    }, Context)

end

function Context:quit()
    context.quit(self.ctx)
end

return Context
