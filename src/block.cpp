
#include "block.h"

Block_2I1O::Block_2I1O(std::function<double(double,double)> func, std::string type_i1, std::string type_i2, std::string type_o):
    mfunc(func),
    mI1(type_i1),
    mI2(type_i2),
    mO(type_o)
{}

void Block_2I1O::Compute()
{

    // check, if assigned
    mI1.check(); mI2.check(); mO.check();
    // check matching types
    if(mI1.type != mI1.getValue().type || mI2.type != mI2.getValue().type )
        throw MyError("Incompatible types", ErrorType::TypeError);

    // count result
    Value result;
    result.type = mO.type;
    result.value = mfunc(mI1.getValue().value, mI2.getValue().value);
    setValue(result);
}

void Block_2I1O::AddWire(Wire * w, int port)
{
    if(port == -1) mO.wire = w;
    else if(port == 1) 
    {
        mI1.wire = w;
        setLevel( MAX(getLevel(), mI1.getLevel()) );
    }
    else if(port == 2) 
    {
        mI2.wire = w;
        setLevel( MAX(getLevel(), mI2.getLevel()) );
    }
    else throw MyError("Unknown port for a vector", ErrorType::WireError);
}

Block_1I1O::Block_1I1O(std::function<double(double)> func, std::string type_i, std::string type_o):
    mfunc(func),
    mI(type_i),
    mO(type_o)
{}

void Block_1I1O::Compute()
{
    Value result;
    if(mI.wire == nullptr || mO.wire == nullptr) throw MyError("The block port is not assigned yet", ErrorType::BlockError);
    if(mI.type != mI.getValue().type) throw MyError("Incompatible types", ErrorType::TypeError);

    result.type = mO.type;
    result.value = mfunc(mI.getValue().value);

    setValue(result);
}

void Block_1I1O::AddWire(Wire * w, int port)
{
    if(port == -1) mO.wire = w;
    else if(port == 1) 
    {
        mI.wire = w;
        setLevel( mI.getLevel() );
    }
    else throw MyError("Unknown port for a vector", ErrorType::WireError);
}
