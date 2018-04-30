

SOURCES = main.cpp defs.cpp controller.cpp playground.cpp guiblock.cpp config.cpp window.cpp model.cpp menu.cpp
HEADERS = defs.h controller.h config.h debug.h playground.h guiblock.h window.h block.h wire.h iblock.h model.h menu.h

TARGET = blockeditor


CONFIG += qt debug
QT += widgets designer
LIBS += -lm
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -DDEBUG_MODE


OBJECTS_DIR=bordel
MOC_DIR=bordel
