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
            mo.addWire(this, mkey, oport);
            mi.addWire(this, mkey, iport);
        }

        ~Wire()
        {
            mo.removeWireKey(mkey);
            mi.removeWireKey(mkey);
        }

        /** @brief Value getter (ask input). */
        Value getValue() const { return mi.getValue(); }
        /** @brief Value setter (set output). */
        void setValue(const Value& value) { mo.setValue(value); }

        /** @brief Level getter (ask input). */
        int getLevel() { return mi.getLevel()+1; }
        void propagateLevel(int level, std::set<int> prop) 
        { 
            mo.propagateLevel(level+1, prop);
        }

    private:
        IBlock& mi; /**< Input block reference. */
        IBlock& mo; /**< Output block reference. */

        long mkey;
        bool mstatus = false;

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

    /** @brief Level getter. */
    int getLevel() { check(); return wire->getLevel(); }
    /** @brief Value getter. */
    Value getValue() { check(); return wire->getValue(); }
    void disconnect() { wire = nullptr; }
    /** @brief Propagate level towards. */
    void propagateLevel(int level, std::set<int> prop) 
    { 
        if(wire != nullptr) wire->propagateLevel(level, prop);
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