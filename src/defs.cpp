// defs.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include "defs.h"

int MyError::getCode()
{
    switch(mcode)
    {
        case ErrorType::BlockError: return 11;
        default: return 42;
    }
}
