
SOURCES = main.cpp defs.cpp model.cpp controller.cpp view.cpp config.cpp
HEADERS = defs.h block.h wire.h iblock.h ioblock.h model.h controller.h view.h config.h debug.h
TARGET = blockeditor


CONFIG += qt debug
QT += widgets
LIBS += -lm
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -DDEBUG_MODE


OBJECTS_DIR=gen
MOC_DIR=gen