TEMPLATE = lib
TARGET = tgs_config
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall
INCLUDEPATH += ../../tgs_core/src

SOURCES += \
    src/config.c

HEADERS += \
    src/config.h
