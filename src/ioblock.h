#ifndef IOBLOCK_H
#define IOBLOCK_H

#include "defs.h"
#include "iblock.h"

/**
 * @brief Input block.
 */
class Input: public IBlock
{
    public:
        /**
         * @brief Input constructor
         * @param value     Initial value of constructor.
         */
        Input(double value = 0) { setValue(value); }

        /**
         * @brief Assigns wire to the port.
         * @param w         Wire to assign.
         * @param port      Port to assign to.
         */
        void AddWire(Wire* w, int port = 0) override
        {
            if(port == -1) mO = w;
            else throw MyError("Input has only output port", ErrorType::BlockError);
        }

    private:
        Wire * mO = nullptr; /**< Output wire. */
};

#endif // IOBLOCK_H