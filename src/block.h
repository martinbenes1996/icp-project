#ifndef BLOCK_H
#define BLOCK_H

#include <functional>
#include <string>

#include "defs.h"
#include "iblock.h"
#include "wire.h"


/**
 * @brief Block.
 */
class Block_2I1O: public IBlock
{
    public:
        /** 
         * @brief Block constructor. 
         * @param func      Functionality of the block.
         * @param type_i1   Type of the 1st input.
         * @param type_i2   Type of the 2nd input.
         * @param type_o    Type of the output.
         */
        Block_2I1O(std::function<double(double,double)>, std::string, std::string, std::string);

        /**
         * @brief Appends wire to the port.
         * @param w     Wire being appended.
         * @param port  Port, to which the wire is being appended.
         */
        void AddWire(Wire *, int port = 0) override;
    
    private:
        std::function<double(double,double)> mfunc; /**< Represents the functionality. */

        Port mI1; /**< Input port 1. */
        Port mI2; /**< Input port 2. */
        Port mO;  /**< Output port. */

        /**
         * @brief Compute the result.
         */
        void Compute();

};




#endif // BLOCK_H