#include "tgs_logger.h"
#include "logger.h"


EXPORT int lua_logger_log(lua_State* ls) {
    TGS_LOGGER* logger = NULL;
    enum TGS_LOG_LEVEL log_level;
    const char* message = NULL;

    if (lua_isuserdata(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3)) {
        logger = lua_touserdata(ls, 1);
        log_level = lua_tonumber(ls, 2);
        message = lua_tostring(ls, 3);
        logger->log(logger, log_level, message);
    } else {
        luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
    }
    return 0;
}


EXPORT int lua_logger_set_level(lua_State* ls) {
    TGS_LOGGER* logger = NULL;
    int log_level = 0;
    if (lua_isuserdata(ls, 1) && lua_isnumber(ls, 2)) {
        logger = lua_touserdata(ls, 1);
        log_level = lua_touserdata(ls, 2);
        logger->set_level(logger, log_level);
    } else {
        luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
    }
    return 0;
}


static const luaL_Reg tgs_logger_lib[] = {
    {"log", lua_logger_log},
    {"set_level", lua_logger_set_level},
    {"LEVEL_DEBUG", NULL},
    {"LEVEL_ERROR", NULL},
    {"LEVEL_INFO", NULL},
    {"LEVEL_WARN", NULL},
    {NULL, NULL}
};


LUAMOD_API int luaopen_logger(lua_State* ls) {
    if (ls != NULL) {
        luaL_newlib(ls, tgs_logger_lib);
        lua_pushnumber(ls, LOG_LEVEL_DEBUG);
        lua_setfield(ls, -2, "LEVEL_DEBUG");
        lua_pushnumber(ls, LOG_LEVEL_ERROR);
        lua_setfield(ls, -2, "LEVEL_ERROR");
        lua_pushnumber(ls, LOG_LEVEL_INFO);
        lua_setfield(ls, -2, "LEVEL_INFO");
        lua_pushnumber(ls, LOG_LEVEL_WARN);
        lua_setfield(ls, -2, "LEVEL_WARN");
    }
    return 1;
}
