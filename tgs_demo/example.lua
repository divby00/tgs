#!/usr/bin/env lua

function vardump(value, depth, key)
    local linePrefix = ''
    local spaces = ''

    if key ~= null then
        linePrefix = "["..key.."] = "
    end

    if depth == nil then
        depth = 0
    else
        depth = depth + 1
        for i=1, depth do spaces = spaces .. "  " end
    end

    if type(value) == 'table' then
        mTable = getmetatable(value)
        if mTable == nil then
            print(spaces .. linePrefix .. "(table) ")
        else
            print(spaces .. "(metatable) ")
            value = mTable
        end
        for tableKey, tableValue in pairs(value) do
            vardump(tableValue, depth, tableKey)
        end
    elseif type(value) == 'function' or type(value) == 'thread' or type(value) == 'userdata' or value == nil then
        print(spaces .. tostring(value))
    else
        print(spaces .. linePrefix .. "(" .. type(value) .. ") " .. tostring(value))
    end
end

-- Lua test
--vardump(context)

print('In!')
local ctx = context.init()
local cfg = context.get_config(ctx)
local log = context.get_logger(ctx)
config.add_field(cfg, "paths", "data", "./data/", config.TYPE_STRING);
config.add_field(cfg, "paths", "lang", "./data/locale/", config.TYPE_STRING);
config.add_field(cfg, "graphics", "fullscreen", "false", config.TYPE_BOOLEAN);
config.add_field(cfg, "graphics", "width", "640", config.TYPE_NUMBER);
config.add_field(cfg, "graphics", "height", "480", config.TYPE_NUMBER);
config.add_field(cfg, "control", "keyboard", "true", config.TYPE_BOOLEAN);
config.add_field(cfg, "control", "joystick", "false", config.TYPE_BOOLEAN);
config.add_field(cfg, "graphics", "height", "480", config.TYPE_NUMBER)
config.read(cfg, "example.json")
context.quit(ctx)
print('Out!')


