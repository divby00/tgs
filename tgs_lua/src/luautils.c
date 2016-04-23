#include "luautils.h"
#include "context.h"
#include "config.h"


/* Context functions */
EXPORT int lua_context_init(lua_State* ls) {
    TGS_CONTEXT* context = NULL;
    context = context_init(0);
    lua_pushlightuserdata(ls, context);
    return 1;
}


EXPORT int lua_context_quit(lua_State* ls) {
    TGS_CONTEXT* context = NULL;
    if (lua_islightuserdata(ls, 1)) {
        context = lua_touserdata(ls, 1);
        context_quit(context);
    }
    return 0;
}


EXPORT int lua_context_get_config(lua_State* ls) {
    TGS_CONTEXT* ctx = NULL;
    TGS_CONFIG* cfg = NULL;

    if (ls != NULL) {
        if (lua_islightuserdata(ls, 1)) {
            ctx = lua_touserdata(ls, 1);
            if (ctx != NULL) {
                cfg = ctx->config;
            }
        }
        lua_pushlightuserdata(ls, cfg);
    }
    return 1;
}


EXPORT int lua_context_get_logger(lua_State* ls) {
    TGS_CONTEXT* ctx = NULL;
    TGS_LOGGER* log = NULL;

    if (ls != NULL) {
        if (lua_isuserdata(ls, 1)) {
            ctx = lua_touserdata(ls, 1);
            if (ctx != NULL) {
                log = ctx->logger;
            }
        } else {
            luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
        }
        lua_pushlightuserdata(ls, log);
    }
    return 1;
}


static const luaL_Reg tgs_context_lib[] = {
    {"init", lua_context_init},
    {"quit", lua_context_quit},
    {"get_config", lua_context_get_config},
    {"get_logger", lua_context_get_logger}
};


LUAMOD_API int luaopen_context(lua_State* ls) {
    if (ls != NULL) {
        luaL_newlib(ls, tgs_context_lib);
    }
    return 1;
}


/* Logger functions */
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


/* Config functions */
EXPORT int lua_config_read(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    const char* filename = NULL;
    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2)) {
        config = lua_touserdata(ls, 1);
        filename = lua_tostring(ls, 2);
        config->read(config, filename);
    } else {
        luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
    }
    return 0;
}


EXPORT int lua_config_save(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    const char* filename = NULL;
    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2)) {
        config = lua_touserdata(ls, 1);
        filename = lua_tostring(ls, 2);
        config->save(config, filename);
    } else {
        luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
    }
    return 0;
}


EXPORT int lua_config_add_field(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    const char* section_name = NULL;
    const char* field_name = NULL;
    const char* field_value = NULL;
    enum TGS_CONFIG_TYPES field_type;

    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3) && lua_isstring(ls, 4) && lua_isnumber(ls, 5)) {
        config = lua_touserdata(ls, 1);
        section_name = lua_tostring(ls, 2);
        field_name = lua_tostring(ls, 3);
        field_value = lua_tostring(ls, 4);
        field_type = lua_tonumber(ls, 5);
        config->add_field(config, section_name, field_name, field_value, field_type);
    } else {
        luaL_error(ls, "Wrong parameters calling backend in function %s", __FUNCTION__);
    }
    return 0;
}


static const luaL_Reg tgs_config_lib[] = {
    {"read", lua_config_read},
    {"save", lua_config_save},
    {"add_field", lua_config_add_field},
    {"TYPE_BOOLEAN", NULL},
    {"TYPE_NUMBER", NULL},
    {"TYPE_STRING", NULL},
    {NULL, NULL}
};


LUAMOD_API int luaopen_config(lua_State* ls) {
    if (ls != NULL) {
        luaL_newlib(ls, tgs_config_lib);
        lua_pushnumber(ls, CFG_TYPE_BOOLEAN);
        lua_setfield(ls, -2, "TYPE_BOOLEAN");
        lua_pushnumber(ls, CFG_TYPE_NUMBER);
        lua_setfield(ls, -2, "TYPE_NUMBER");
        lua_pushnumber(ls, CFG_TYPE_STRING);
        lua_setfield(ls, -2, "TYPE_STRING");
    }
    return 1;
}
