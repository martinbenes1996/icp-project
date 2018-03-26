
SOURCES = src/main.cpp src/defs.cpp src/block.cpp
HEADERS = src/defs.h src/block.h src/wire.h src/iblock.h src/ioblock.h
TARGET = blockeditor


CONFIG += qt debug
QT += widgets
LIBS += -lm
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic


OBJECTS_DIR=gen
MOC_DIR=gen