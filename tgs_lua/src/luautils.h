#ifndef __LUAUTILS_H__
#define __LUAUTILS_H__


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


#ifdef WIN32
    #ifdef BUILD_DLL
        /* DLL export */
        #define EXPORT __declspec(dllexport)
    #else
        /* EXE import */
        /*#define EXPORT __declspec(dllimport)*/
        #define EXPORT
    #endif
#else
    #define EXPORT
#endif

EXPORT int lua_config_init(lua_State* ls);
EXPORT int lua_config_quit(lua_State* ls);
EXPORT int lua_config_read(lua_State* ls);
EXPORT int lua_config_save(lua_State* ls);
EXPORT int lua_context_get_config(lua_State* ls);
EXPORT int lua_context_get_logger(lua_State* ls);

#endif
