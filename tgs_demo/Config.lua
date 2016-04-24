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


function Config:add_field(section, field, value, field_type)
    config.add_field(self._config, section, field, value, field_type)
end


function Config:get_boolean(section, field)
    return config.get_boolean(self._config, section, field)
end


function Config:get_number(section, field)
    return config.get_number(self._config, section, field)
end


function Config:get_string(section, field)
    return config.get_string(self._config, section, field)
end


return Config;
