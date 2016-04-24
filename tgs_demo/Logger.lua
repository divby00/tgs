local Logger = {}
Logger.__index = Logger


function Logger:new(ctx)
    _logger = context.get_logger(ctx)
    return setmetatable({
        _logger = _logger
    }, Logger)
end


function Logger:log(log_level, message)
    logger.log(self._logger, log_level, message)
end


return Logger
