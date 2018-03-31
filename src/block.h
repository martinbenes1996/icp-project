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
template <class T> class Block_2I1O: public IBlock
{
    public:
        /** 
         * @brief Block constructor. 
         * @param func      Functionality of the block.
         * @param intypes   Types of inputs.
         * @param outtypes  Types of input.
         * @param type_o    Type of the output.
         */
        Block(T, std::string, std::vector<std::string>, std::string);

        /**
         * @brief Appends wire to the port.
         * @param w     Wire being appended.
         * @param key   Key of the wire.
         * @param port  Port, to which the wire is being appended.
         */
        void AddWire(Wire *, long, int port = 0) override;

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        void setLevel(int) override;
    
    private:
        T mfunc; /**< Represents the functionality. */

        std::vector<Port> mIn;
        std::vector<Port> mOut;

        /**
         * @brief Compute the result.
         */
        void Compute();
        void Compute(std::function<double(double,double)>);

};




#endif // BLOCK_H