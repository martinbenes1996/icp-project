/**
 * @file iblock.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief module objects interface
 *
 * This module contains interface IBlock, used in module.
 */

#ifndef IBLOCK_H
#define IBLOCK_H

#include <map>
#include <set>

#include "defs.h"
#include "debug.h"

class Wire;

/**
 * @brief IBlock interface.
 */
class IBlock
{
    public:
        /**
         * @brief IBlock constructor.
         * @param id        ID of the block.
         * @param type      Type of the block.
         */
        IBlock(long id, long type = -1): mid(id), mtype(type) {}
        /**
         * @brief IBlock destructor.
         */
        virtual ~IBlock() {}

        /**
         * @brief Value getter.
         * @returns The block value.
         */
        virtual Value getValue() const { return mvalue; }
        /**
         * @brief Value setter.
         * @param value     Assigned value.
         */
        virtual void setValue(const Value& value) { mvalue = value; }
        /**
         * @brief Value resetter.
         */
        void resetValue() { Value v; setValue(v); }

        /**
         * @brief Level setter.
         * @param level     New level value.
         */
        virtual void setLevel(int level) { mlevel = level; }
        /**
         * @brief Level getter.
         * @returns The level value.
         */
        virtual int getLevel() const { return mlevel; }

        /**
         * @brief Type getter.
         * @returns The type value.
         */
        long getType() const { return mtype; }

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
        virtual void removeWireKey(long key) { Debug::Block("IBlock::removeWireKey("+std::to_string(key)+")"); mkeys.erase(key); }
        /**
         * @brief Getter of keys of associated wires.
         * @returns Set of keys.
         */
        std::map<long,int> getWireKeys() const { return mkeys; }
        
        /**
         * @brief Input indicator.
         * @returns True, weather the block is input, false otherwise.
         */
        virtual bool isInput() { return false; }

        /**
         * @brief Distributes the result forward. It is overriden in the child classes.
         * @returns Results from following blocks (here are none).
         */
        virtual SimulationResults distributeResult() { return SimulationResults(); }
        /**
         * @brief Distributes the result from previous forward, merges and returns.
         *        It is overriden in the child classes.
         * @param r         Previous results.
         * @returns Results from following blocks (here are none).
         */
        virtual SimulationResults& distributeResult(SimulationResults& r) { return r; }

    protected:
        /**
         * @brief ID getter.
         * @returns ID.
         */
        long getId() const { return mid; }

        /**
         * @brief Input port indicator.
         * @param p         Port to test.
         * @returns True, if the given port is input.
         */
        static bool isInputPort(int p) { return p >= 0; }
        /**
         * @brief Output port indicator.
         * @param p         Port to test.
         * @returns TRue, if the given port is output.
         */
        static bool isOutputPort(int p) { return p < 0; }

    private:
        long mid; /**< ID of the block. */
        long mtype; /**< Type of the block. */

        Value mvalue; /**< Value, that a block counted/has. */
        int mlevel = -1; /**< Level of the block in the scheme. */

        std::map<long,int> mkeys; /**< Keys of the wires connected () */
};

#endif // IBLOCK_H
