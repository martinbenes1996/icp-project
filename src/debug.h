
/**
 * @file debug.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief Debug interface
 *
 * This module supports the debug system in whole project.
 */


#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

// switches to set debug informations to show
#ifdef DEBUG_MODE
    //#define BLOCK_DEBUG
    //#define MODEL_DEBUG
    //#define EVENTS_DEBUG
    //#define GUI_DEBUG
    //#define CONTROLLER_DEBUG
    //#define COMPUTE_DEBUG
    //#define FILE_DEBUG
    //...
#endif // DEBUG_MODE

/**
 * @brief Namespace for debug methods.
 */
namespace Debug
{
    /**
     * @brief Block debug.
     * @param str       String to print.
     */
    inline void Block(std::string str) {
        #ifdef BLOCK_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief Model debug.
     * @param str       String to print.
     */
    inline void Model(std::string str) {
        #ifdef MODEL_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief User events debug.
     * @param str       String to print.
     */
    inline void Events(std::string str) {
        #ifdef EVENTS_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief Graphics debug.
     * @param str       String to print.
     */
    inline void Gui(std::string str) {
        #ifdef GUI_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief Controller debug.
     * @param str       String to print.
     */
    inline void Controller(std::string str) {
        #ifdef CONTROLLER_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief Computation debug.
     * @param str       String to print.
     */
    inline void Compute(std::string str) {
        #ifdef COMPUTE_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
    /**
     * @brief Loading and saving debug.
     * @param str       String to print.
     */
    inline void File(std::string str) {
        #ifdef FILE_DEBUG
            std::cerr << str << "\n";
        #endif
        (void)str;
    }
}

#endif // DEBUG_H
