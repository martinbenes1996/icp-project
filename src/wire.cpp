
#include "wire.h"

Wire::Wire(IBlock& i, int iport,
     IBlock& o, int oport):
    mi(i),
    mo(o) 
{
    mi.AddWire(this, iport);
    mo.AddWire(this, oport);
}