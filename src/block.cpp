
#include "block.h"

Block_2I1O::Block_2I1O(std::function<double(double,double)> func, std::string type_i1, std::string type_i2, std::string type_o):
    mfunc(func),
    mI1(type_i1),
    mI2(type_i2),
    mO(type_o)
{}

void Block_2I1O::Compute()
{
    Value result;
    if(mI1.wire == nullptr || mI2.wire == nullptr || mO.wire == nullptr) throw MyError("The block port is not assigned yet", ErrorType::BlockError);
    if(mI1.type != mI1.wire->getValue().type || mI2.type != mI2.wire->getValue().type ) throw MyError("Incompatible types", ErrorType::TypeError);

    result.type = mO.type;
    result.value = mfunc(mI1.wire->getValue().value, mI2.wire->getValue().value);

    setValue(result);
}

void Block_2I1O::AddWire(Wire * w, int port)
{
    if(port == -1) mO.wire = w;
    else if(port == 1) mI1.wire = w;
    else if(port == 2) mI2.wire = w;
    else throw MyError("Unknown port for a vector", ErrorType::WireError);
}
