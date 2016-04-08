TEMPLATE = app
TARGET = tgs_demo
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
INCLUDEPATH += ../tgs_core/src
INCLUDEPATH += ../tgs_modules/tgs_config/src
INCLUDEPATH += ../tgs_sdl2/src
INCLUDEPATH += ../tgs_lua/src
LIBS += ../tgs_lua/libtgs_lua.a
LIBS += ../tgs_sdl2/libtgs_sdl2.a
LIBS += ../tgs_modules/tgs_config/libtgs_config.a
LIBS += ../tgs_core/libtgs_core.a
LIBS += -lSDL2
PRE_TARGETDEPS += ../tgs_lua
PRE_TARGETDEPS += ../tgs_sdl2
PRE_TARGETDEPS += ../tgs_modules/tgs_config
PRE_TARGETDEPS += ../tgs_core
OBJECTS_DIR = src/obj
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console
CONFIG += debug
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
SOURCES += src/demo.c

DISTFILES += \
    example.json \
    example.lua
