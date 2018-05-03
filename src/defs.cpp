// defs.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


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
