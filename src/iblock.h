#ifndef IBLOCK_H
#define IBLOCK_H

#include "defs.h"

class Wire;
/**
 * @brief IBlock interface.
 */
class IBlock
{
    public:
        /**
         * @brief Value getter.
         * @returns The block value.
         */
        virtual Value getValue() const {
            if(mcounted) return mvalue;
            else throw MyError("The block value is not assigned yet", ErrorType::BlockError);
        }
        /**
         * @brief Value setter.
         * @param value     Assigned value.
         */
        virtual void setValue(const Value& value) { mvalue = value; }

        /**
         * @brief Assigns wire to the port.
         * @param w         Wire to assign.
         * @param port      Port to assign to.
         */
        virtual void AddWire(Wire* w, int port = 0) = 0;

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        virtual void setLevel(int level) { mlevel = level; }
        /**
         * @brief Level getter.
         * @returns The level value.
         */
        int getLevel() const 
        { 
            if(mlevel != -1) return mlevel;
            else throw MyError("Level not assigned to the block", ErrorType::BlockError); 
        }
    
    private:
        Value mvalue; /**< Value. */
        bool mcounted = false; /**< Value already counted. */

        int mlevel = -1; /**< Level. */
};

#endif // IBLOCK_H