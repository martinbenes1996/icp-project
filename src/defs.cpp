
#include "defs.h"

int MyError::getCode()
{ 
    switch(mcode)
    {
        case ErrorType::BlockError: return 11;
        default: return 42;
    }
}