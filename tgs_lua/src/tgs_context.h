#ifndef TGS_CONTEXT_H
#define TGS_CONTEXT_H


#include "luautils.h"


EXPORT int lua_context_get_config(lua_State* ls);
EXPORT int lua_context_get_logger(lua_State* ls);


#endif // TGS_CONTEXT_H
