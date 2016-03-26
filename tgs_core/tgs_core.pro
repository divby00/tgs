TEMPLATE = lib
TARGET = tgs_core
QMAKE_LIBDIR = /usr/lib/x86_64-linux-gnu
OBJECTS_DIR = src/obj
CONFIG -= app_bundle qt
CONFIG += console debug staticlib
QMAKE_CFLAGS = -pedantic -std=c99 -Wall

SOURCES += src/memory.c \
    src/logger.c \
    src/stringutils.c \
    src/linkedlist.c \
    src/hashtable.c \
    src/json.c \
    src/memmngr.c

HEADERS += \
    src/memory.h \
    src/logger.h \
    src/stringutils.h \
    src/linkedlist.h \
    src/hashtable.h \
    src/json.h \
    src/memmngr.h
