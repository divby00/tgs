#!/usr/bin/env lua


local Context = require 'Context'


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
    else print(spaces .. linePrefix .. "(" .. type(value) .. ") " .. tostring(value))
    end
end


function setup(ctx)
    local cfg = ctx:get_config()
    cfg:add_field('paths', 'data', './data', config.TYPE_STRING)
    cfg:add_field('paths', 'lang', './data/locale', config.TYPE_STRING)
    cfg:add_field('graphics', 'fullscreen', 'false', config.TYPE_BOOLEAN)
    cfg:add_field('graphics', 'width', '640', config.TYPE_NUMBER)
    cfg:add_field('graphics', 'height', '480', config.TYPE_NUMBER)
    cfg:add_field('control', 'keyboard', 'true', config.TYPE_BOOLEAN)
    cfg:add_field('control', 'joystick', 'false', config.TYPE_BOOLEAN)
    cfg:read('config.json')
end


function main()
    local ctx = Context:new()
    local log = ctx:get_logger()
    log:log(logger.LEVEL_DEBUG, 'Running demo...')
    setup(ctx)
    ctx:quit()
end


main()
