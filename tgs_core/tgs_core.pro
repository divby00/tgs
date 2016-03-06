TEMPLATE = lib
TARGET = tgs_core
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall

SOURCES += src/memory.c \
    src/list.c \
    src/logger.c \
    src/stringutils.c

HEADERS += \
    src/memory.h \
    src/typealias.h \
    src/list.h \
    src/logger.h \
    src/sizes.h \
    src/stringutils.h
