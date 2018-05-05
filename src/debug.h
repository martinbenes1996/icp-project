// debug.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef DEBUG_MODE
    //#define BLOCK_DEBUG
    //#define MODEL_DEBUG
    //#define EVENTS_DEBUG
    //#define GUI_DEBUG
    //#define CONTROLLER_DEBUG
    //#define COMPUTE_DEBUG
    #define FILE_DEBUG
    //...
#endif // DEBUG_MODE

namespace Debug
{
    inline void Block(std::string str) {
        #ifdef BLOCK_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void Model(std::string str) {
        #ifdef MODEL_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void Events(std::string str) {
        #ifdef EVENTS_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void Gui(std::string str) {
        #ifdef GUI_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void Controller(std::string str) {
        #ifdef CONTROLLER_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void Compute(std::string str) {
        #ifdef COMPUTE_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }

    inline void File(std::string str) {
        #ifdef FILE_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
}

#endif // DEBUG_H
