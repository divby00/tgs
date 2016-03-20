TEMPLATE = lib
TARGET = tgs_lua
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
INCLUDEPATH += ../tgs_core/src
INCLUDEPATH += ../tgs_sdl2/src

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
    src/lcorolib.c \
    src/ldblib.c \
    src/liolib.c \
    src/lmathlib.c \
    src/loslib.c \
    src/lstrlib.c \
    src/ltablib.c \
    src/lutf8lib.c \
    src/loadlib.c \
    src/linit.c \
