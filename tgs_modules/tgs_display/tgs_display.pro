TEMPLATE = lib
TARGET = tgs_display
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
INCLUDEPATH += ../../tgs_core/src

SOURCES += \
    src/display.c

HEADERS += \
    src/display.h

