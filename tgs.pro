TEMPLATE = subdirs
VERSION = 0.1
CONFIG -= qt
CONFIG += console
CONFIG += debug
SUBDIRS = tgs_core \
          tgs_modules \
          tgs_context \
          tgs_lua \
          tgs_demo
tgs_demo.depends = tgs_core tgs_modules tgs_context tgs_lua
