local Config = require 'Config'

local Context = {}
Context.__index = Context

function Context:new()
    ctx = context.init()
    cfg = context.get_config(ctx)
    return setmetatable({
        ctx = ctx,
        cfg = cfg
    }, Context)
end

function Context:quit()
    print(self.ctx)
    context.quit(self.ctx)
end

return Context
