#include "luautils.h"
#include "config.h"


EXPORT int lua_config_init(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    config = config_init();
    lua_pushlightuserdata(ls, config);
    return 1;
}

EXPORT int lua_config_quit(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    if (lua_isuserdata(ls, 1)) {
        config = lua_touserdata(ls, 1);
        config_quit(config);
    }
    return 0;
}

EXPORT int lua_config_read(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    char* filename = NULL;
    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2)) {
        config = lua_touserdata(ls, 1);
        filename = lua_tostring(ls, 2);
        config->read(config, filename);
    }
    return 0;
}

EXPORT int lua_config_save(lua_State* ls) {
    TGS_CONFIG* config = NULL;
    char* filename = NULL;
    if (lua_isuserdata(ls, 1) && lua_isstring(ls, 2)) {
        config = lua_touserdata(ls, 1);
        filename = lua_tostring(ls, 2);
        config->save(config, filename);
    }
    return 0;
}


static const luaL_Reg tgs_lib[] = {
    {"config_init", lua_config_init},
    {"config_quit", lua_config_quit},
    {"config_read", lua_config_read},
    {"config_save", lua_config_save},
    {NULL, NULL}
};


LUAMOD_API int luaopen_tgs(lua_State* ls) {
    if (ls != NULL) {
        luaL_newlib(ls, tgs_lib);
    }
    return 1;
}
