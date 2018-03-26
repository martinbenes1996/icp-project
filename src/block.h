#ifndef BLOCK_H
#define BLOCK_H

#include <functional>
#include <string>

#include "defs.h"
#include "iblock.h"
#include "wire.h"


/**
 * @brief Block, 2 inputs and 1 output.
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

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        void setLevel(int) override;
    
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

/**
 * @brief Block, 1 input and 1 output.
 */
class Block_1I1O: public IBlock
{
    public:
        /** 
         * @brief Block constructor. 
         * @param func      Functionality of the block.
         * @param type_i   Type of the input.
         * @param type_o    Type of the output.
         */
        Block_1I1O(std::function<double(double)>, std::string, std::string);

        /**
         * @brief Appends wire to the port.
         * @param w     Wire being appended.
         * @param port  Port, to which the wire is being appended.
         */
        void AddWire(Wire *, int port = 0) override;

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        void setLevel(int) override;
    
    private:
        std::function<double(double)> mfunc; /**< Represents the functionality. */

        Port mI; /**< Input port 1. */
        Port mO;  /**< Output port. */

        /**
         * @brief Compute the result.
         */
        void Compute();

};




#endif // BLOCK_H