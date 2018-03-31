#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef DEBUG_MODE
    #define BLOCK_DEBUG
    //...
#endif // DEBUG_MODE

namespace Debug
{
    void Block(std::string str) {
        #ifdef BLOCK_DEBUG
            std::cerr << str << "\n";
        #endif
    }
}

#endif // DEBUG_H