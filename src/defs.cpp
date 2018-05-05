
/**
 * @file defs.cpp
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief Global types
 *
 * This module contains a defs definitions.
 */


#include "defs.h"

namespace {
    int maxLevel = -1;
}

int MyError::getCode()
{
    switch(mcode)
    {
        case ErrorType::BlockError: return 11;
        default: return 42;
    }
}

int SimulationResults::getMaxLevel() { return maxLevel; }
void SimulationResults::setMaxLevel(int max) { maxLevel = max; }
void SimulationResults::resetMaxLevel() { maxLevel = -1; }
