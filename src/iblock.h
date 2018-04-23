#ifndef IBLOCK_H
#define IBLOCK_H

#include <map>
#include <set>

#include "defs.h"

class Wire;

/**
 * @brief Value in the block or on the wire,
 */
struct Value {
    std::string type; /**< Type of the value. */
    double value = 0; /**< Value itself. */
    bool valid = false;
};

/**
 * @brief IBlock interface.
 */
class IBlock
{
    public:
        IBlock(long id): mid(id) {}
        virtual ~IBlock() {}

        /**
         * @brief Value getter.
         * @returns The block value.
         */
        virtual Value getValue() const
        {
            if(mvalue.valid) return mvalue;
            else throw MyError("The block value is not assigned yet", ErrorType::BlockError);
        }

        /**
         * @brief Value setter.
         * @param value     Assigned value.
         */
        virtual void setValue(const Value& value) { mvalue = value; }

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

        /**
         * @brief Propagates level towards.
         * @param level     Propagated level.
         */
        virtual void propagateLevel(int, std::set<int>) {}

        /**
         * @brief Assigns wire to the port.
         * @param w         Wire to assign.
         * @param key       Key of the wire.
         * @param port      Port to assign to.
         */
        virtual void addWire(Wire*, long key, int port = 0) 
        { 
            mkeys.insert( std::make_pair(key,port) );
        }

        /**
         * @brief Removes a single wire key.
         * @param key       Key of wire to remove.
         */
        virtual void removeWireKey(long key) { mkeys.erase(key); }

        /**
         * @brief Getter of keys of associated wires.
         * @returns Set of keys.
         */
        std::map<long,int> getWireKeys() const { return mkeys; }


    protected:

        long getId() const { return mid; }

        static bool isInputPort(int p) { return p >= 0; }
        static bool isOutputPort(int p) { return p < 0; }
    
    private:
        long mid;

        Value mvalue; /**< Value, that a block counted/has. */
        int mlevel = -1; /**< Level of the block in the scheme. */

        std::map<long,int> mkeys; /**< Keys of the wires connected () */
};

#endif // IBLOCK_H