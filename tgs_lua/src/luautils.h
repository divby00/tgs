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


#endif
