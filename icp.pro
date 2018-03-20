
SOURCES = src/hello.cpp
HEADERS = src/hello.h
TARGET = icp


CONFIG += qt debug
QT += widgets
LIBS += -lm
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic


OBJECTS_DIR=gen
MOC_DIR=gen