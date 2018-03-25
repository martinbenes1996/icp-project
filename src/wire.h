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
        Wire(IBlock&, int, IBlock&, int);

        /** @brief Value getter (ask input). */
        Value getValue() const { return mi.getValue(); }
        /** @brief Value setter (set output). */
        void setValue(const Value& value) { mo.setValue(value); }

    private:
        IBlock& mi; /**< Input block reference. */
        IBlock& mo; /**< Output block reference. */

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
};

#endif // WIRE_H