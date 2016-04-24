local Config = require 'Config'
local Logger = require 'Logger'
local Context = {}
Context.__index = Context


function Context:new()
    _context = context.init()
    Config = Config:new(_context)
    Logger = Logger:new(_context)

    return setmetatable({
        _context = _context,
        Config = Config,
        Logger = Logger
    }, Context)
end


function Context:get_config()
    return self.Config
end


function Context:get_logger()
    return self.Logger
end


function Context:quit()
    context.quit(self._context)
end


return Context
