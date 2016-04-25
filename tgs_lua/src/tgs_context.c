#include "tgs_context.h"
#include "context.h"


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
