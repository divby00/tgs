local Config = {}
Config.__index = Config

function Config:new(ctx)
    _config = context.get_config(ctx)
    return setmetatable({
        _config = _config
    }, Config)
end

function Config:read(filename)
    config.read(self._config, filename)
end

return Config;
