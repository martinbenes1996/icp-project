#ifndef IBLOCK_H
#define IBLOCK_H

#include <vector>

#include "defs.h"

class Wire;

/**
 * @brief Value in the block or on the wire,
 */
struct Value {
    std::string type; /**< Type of the value. */
    double value = 0; /**< Value itself. */
};

/**
 * @brief IBlock interface.
 */
class IBlock
{
    public:
        virtual ~IBlock() {}

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
         * @param key       Key of the wire.
         * @param port      Port to assign to.
         */
        virtual void AddWire(Wire*, long key, int port = 0) { mkeys.push_back(key); (void)port; }

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        virtual void setLevel(int level) { mlevel = level; }
        /**
         * @brief Level getter.
         * @returns The level value.
         */
        int getLevel() const { return mlevel; }

        std::vector<long> getWireKeys() const { return mkeys; }
    
    private:
        Value mvalue; /**< Value. */
        bool mcounted = false; /**< Value already counted. */

        int mlevel = 0; /**< Level. */

        std::vector<long> mkeys;
};

#endif // IBLOCK_H