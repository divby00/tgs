local Config = {}
Config.__index = Config

function Config:new()
    return setmetatable({}, Config)
end

function Config:read()
    print('Config read...')
end

return Config;
