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
        /** @brief Value getter. */
        virtual Value getValue() const {
            if(mcounted) return mvalue;
            else throw MyError("The block value is not assigned yet", ErrorType::BlockError);
        }
        /** @brief Value setter. */
        virtual void setValue(const Value& value) { mvalue = value; }

        virtual void AddWire(Wire* w, int port = 0) = 0;

        void setLevel(int level) { mlevel = level; }
        int getLevel() const 
        { 
            if(mlevel != -1) return mlevel;
            else throw MyError("Level not assigned to the block", ErrorType::BlockError); 
        }
    
    private:
        Value mvalue; /**< Value. */
        bool mcounted = false; /**< Value already counted. */

        int mlevel = -1;
};

#endif // IBLOCK_H