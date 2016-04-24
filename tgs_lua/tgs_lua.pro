TEMPLATE = lib
TARGET = tgs_lua
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
INCLUDEPATH += ../tgs_core/src
INCLUDEPATH += ../tgs_modules/tgs_config/src
INCLUDEPATH += ../tgs_modules/tgs_display/src
INCLUDEPATH += ../tgs_context/src

SOURCES += src/lapi.c \
    src/lcode.c \
    src/lctype.c \
    src/ldebug.c \
    src/ldo.c \
    src/ldump.c \
    src/lfunc.c \
    src/lgc.c \
    src/llex.c \
    src/lmem.c \
    src/lobject.c \
    src/lopcodes.c \
    src/lparser.c \
    src/lstate.c \
    src/lstring.c \
    src/ltable.c \
    src/ltm.c \
    src/lundump.c \
    src/lvm.c \
    src/lzio.c \
    src/lauxlib.c \
    src/lbaselib.c \
    src/lbitlib.c \
    src/ltablib.c \
    src/loadlib.c \
    src/linit.c \
    src/luautils.c \
    src/lauxlib.h


HEADERS += \
    src/luautils.h \
    src/lcode.h \
    src/lctype.h \
    src/ldebug.h \
    src/ldo.h \
    src/lfunc.h \
    src/lgc.h \
    src/llex.h \
    src/llimits.h \
    src/lmem.h \
    src/lobject.h \
    src/lopcodes.h \
    src/lparser.h \
    src/lprefix.h \
    src/lstate.h \
    src/lstring.h \
    src/ltable.h \
    src/ltm.h \
    src/luaconf.h \
    src/lua.h \
    src/lualib.h \
    src/luautils.h \
    src/lundump.h \
    src/lvm.h \
    src/lzio.h
