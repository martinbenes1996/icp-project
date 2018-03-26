#ifndef IOBLOCK_H
#define IOBLOCK_H

#include "defs.h"
#include "iblock.h"

class Input: public IBlock
{
    public:
        Input(double value = 0) { setValue(value); }

        void AddWire(Wire* w, int port = 0) override
        {
            if(port == -1) mO = w;
            else throw MyError("Input has only output port", ErrorType::BlockError);
        }

    private:
        Wire * mO = nullptr;
};

#endif // IOBLOCK_H