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
    if (lua_isuserdata(ls, 1)) {
        context = lua_touserdata(ls, 1);
        context_quit(context);
    }
    return 0;
}


EXPORT int lua_context_get_config(lua_State* ls) {
    TGS_CONTEXT* ctx = NULL;
    TGS_CONFIG* cfg = NULL;

    if (ls != NULL) {
        if (lua_isuserdata(ls, 1)) {
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


/* Config functions */
EXPORT int lua_config_read(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    const char* filename = NULL;
    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2)) {
        config = lua_touserdata(ls, 1);
        filename = lua_tostring(ls, 2);
        config->read(config, filename);
    } else {
        luaL_error(ls, "Wrong parameters calling config->read");
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
        luaL_error(ls, "Wrong parameters calling config->save");
    }
    return 0;
}


EXPORT int lua_config_add_field(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    const char* section_name = NULL;
    const char* field_name = NULL;
    const char* field_value = NULL;
    enum TGS_CONFIG_TYPES field_type;

    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3) && lua_isstring(ls, 4) && lua_isfunction(ls, 5)) {
        config = lua_touserdata(ls, 1);
        section_name = lua_tostring(ls, 2);
        field_name = lua_tostring(ls, 3);
        field_value = lua_tostring(ls, 4);
        field_type = lua_tonumber(ls, 5);
        config->add_field(config, section_name, field_name, field_value, field_type);
    } else {
        luaL_error(ls, "Wrong parameters calling config->add_field");
    }
    return 0;
}


static const luaL_Reg tgs_config_lib[] = {
    {"TYPE_BOOLEAN", CFG_TYPE_BOOLEAN},
    {"TYPE_NUMBER", CFG_TYPE_NUMBER},
    {"TYPE_STRING", CFG_TYPE_STRING},
    {"read", lua_config_read},
    {"save", lua_config_save},
    {"add_field", lua_config_add_field},
    {NULL, NULL}
};


LUAMOD_API int luaopen_config(lua_State* ls) {
    if (ls != NULL) {
        luaL_newlib(ls, tgs_config_lib);
    }
    return 1;
}
