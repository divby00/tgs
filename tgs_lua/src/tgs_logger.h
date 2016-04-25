#ifndef TGS_LOGGER_H
#define TGS_LOGGER_H


#include "luautils.h"


EXPORT int lua_logger_log(lua_State* ls);
EXPORT int lua_logger_set_level(lua_State* ls);


#endif
