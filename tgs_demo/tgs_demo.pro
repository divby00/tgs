TEMPLATE = app
TARGET = tgs_demo
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
INCLUDEPATH += ../tgs_core/src
INCLUDEPATH += ../tgs_sdl2/src
LIBS += ../tgs_core/libtgs_core.a
LIBS += ../tgs_sdl2/libtgs_sdl2.a
PRE_TARGETDEPS += ../tgs_core
PRE_TARGETDEPS += ../tgs_sdl2
OBJECTS_DIR = src/obj
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console
CONFIG += debug
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
SOURCES += src/demo.c
