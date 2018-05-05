
/**
 * @file wire.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief wire and port
 *
 * This module contains model wire definition.
 */

#ifndef WIRE_H
#define WIRE_H

#include "defs.h"
#include "iblock.h"

/**
 * @brief Wire.
 */
class Wire
{
    public:
        /**
         * @brief Wire constructor.
         * @param i     Input block.
         * @param iport Input block port.
         * @param o     Output block.
         * @param oport Output block port.
         */
        Wire(long key, IBlock& i, int iport, IBlock& o, int oport):
            mi(i), mo(o), mkey(key)
        {
            try { 
                mo.addWire(this, mkey, oport);
                mi.addWire(this, mkey, iport);
            } catch(MyError& e) { 
                mo.removeWireKey(mkey); 
                mi.removeWireKey(mkey);
                throw e;
            }
        }

        /**
         * @brief Wire destructor.
         */
        ~Wire()
        {
            mo.removeWireKey(mkey);
            mi.removeWireKey(mkey);
        }

        /**
         * @brief Value getter (ask input).
         * @returns Value of the input block.
         */
        Value getValue() const { return mi.getValue(); }
        /**
         * @brief Value setter (set output).
         * @param value         New value to set.
         */
        void setValue(const Value& value) { mo.setValue(value); }

        /**
         * @brief Level getter.
         * @returns Incremented input block level.
         */
        int getLevel() { return mi.getLevel()+1; }
        /**
         * @brief Propagates level from input to output.
         * @param level         Level to propagate.
         * @param prop          Set with block keys.
         */
        void propagateLevel(int level, std::set<int> prop)
        {
            mo.propagateLevel(level+1, prop);
        }
        
        /**
         * @brief Distributes result from input to output.
         * @param sr            Results.
         * @returns Merged results.
         */
        SimulationResults& distributeResult(SimulationResults& sr) const
        {
            Debug::Block("Wire::distributeResult()");
            Result r;
            Value v = mi.getValue();

            r.level = mi.getLevel();
            r.value = v.value;
            r.type = v.type;

            sr.insertWire(mkey,r);
            return mo.distributeResult(sr);
        }

    private:
        IBlock& mi; /**< Input block reference. */
        IBlock& mo; /**< Output block reference. */

        long mkey;  /**< Key of the wire. */
        bool mstatus = false; /**< Status of the wire. */

};

/**
 * @brief Port of the block.
 */
struct Port
{
    /** @brief Port constructor. */
    Port(std::string t, Wire* w = nullptr): type(t), wire(w) {}

    std::string type = ""; /* Type, that port accepts. */
    Wire* wire = nullptr;  /* Wire pointer. */

    /** 
     * @brief Level getter.
     * @returns Level.
     */
    int getLevel() { check(); return wire->getLevel(); }
    /**
     * @brief Value getter.
     * @returns Value.
     */
    Value getValue() { check(); return wire->getValue(); }
    /**
     * @brief Disconnects connected wire.
     */
    void disconnect() { wire = nullptr; }
    /**
     * @brief Propagate level towards.
     * @param level     Propagated level value.
     * @param prop      Set of keys of blocks already seen.
     */
    void propagateLevel(int level, std::set<int> prop)
    {
        if(wire != nullptr) wire->propagateLevel(level, prop);
    }
    /**
     * @brief Distributes result from input to output.
     * @param sr            Results.
     * @returns Merged results.
     */
    SimulationResults& distributeResult(SimulationResults& r) const 
    {
        if(wire == nullptr) return r;
        else return wire->distributeResult(r);
    }

    /**
     * @brief Checks, wheather the port has assigned wire. Throws, if not.
     */
    void check()
    {
        if(wire == nullptr)
            throw MyError("Port not assigned", ErrorType::WireError);
    }
};


#endif // WIRE_H
