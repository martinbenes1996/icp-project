#ifndef BLOCK_H
#define BLOCK_H

#include <functional>
#include <set>
#include <string>

#include "debug.h"
#include "defs.h"
#include "iblock.h"
#include "wire.h"


/**
 * @brief Block.
 */
template <class T>
class Block: public IBlock
{
    public:
        /** 
         * @brief Block constructor. 
         * @param func      Functionality of the block.
         * @param intypes   Types of inputs.
         * @param outtypes  Types of input.
         * @param type_o    Type of the output.
         */
        Block(T func, std::vector<std::string> intypes, std::vector<std::string> outtypes):
            mfunc(func)
        {
            for(auto& it: intypes) { mIn.push_back(it); }
            for(auto& it: outtypes) { mOut.push_back(it); }
        }

        /**
         * @brief Appends wire to the port.
         * @param w     Wire being appended.
         * @param key   Key of the wire.
         * @param port  Port, to which the wire is being appended.
         */
        inline void AddWire(Wire *, long, int port = 0) override;

        /**
         * @brief Level setter. 
         * @param level     New level value.     
         */
        inline void setLevel(int) override;

    
    private:
        T mfunc; /**< Represents the functionality. */

        std::vector<Port> mIn;
        std::vector<Port> mOut;
        void CheckTypes(std::vector<Port>&);

        /**
         * @brief Compute the result.
         */
        void Compute();
        Value Compute(T) { throw MyError("Not implemented computation.", ErrorType::MathError); }

};


template <class T>
void Block<T>::setLevel(int level)
{
    IBlock::setLevel(level);
    for(auto& it: mOut) { if(it.wire != nullptr) it.wire->propagateLevel(); }
}

template <class T>
void Block<T>::AddWire(Wire *w, long key, int port)
{
    Debug::Block("Block::AddWire");
    std::vector<Port>& v = (port < 0)?mOut:mIn;
    int index = (port < 0) ? (-port-1):(port);
    
    try
    {  
        // connect wire
        if(v[index].wire == nullptr) v[index].wire = w;
        // already connected port
        else throw MyError("Adding wire to connected port", ErrorType::WireError);
        
        // add to keys
        IBlock::AddWire(w, key, port);
    }
    catch(std::exception& ex) { throw MyError("Not an existing port", ErrorType::BlockError); }
}

template <class T>
void Block<T>::CheckTypes(std::vector<Port>& v)
{
    for(auto& it: v)
    {
        it.check();
        if(it.type != it.getValue().type)
            throw MyError("Incompatible types", ErrorType::TypeError);
    }
}

template <class T>
void Block<T>::Compute()
{
    Debug::Block("Block::Compute");

    // check matching types
    CheckTypes(mIn);
    CheckTypes(mOut);
    
    // count result
    setValue( Compute(mfunc) );
}

template<>
Value Block<std::function<double(double,double)>>::Compute(std::function<double(double,double)>) 
{
    Value v;
    v.type = mOut[0].type;
    v.value = mfunc(mIn[0].getValue().value, mIn[1].getValue().value);
    v.valid = true;
    return v;
}

template<>
Value Block<std::function<double(double)>>::Compute(std::function<double(double)>) 
{
    Value v;
    v.type = mOut[0].type;
    v.value = mfunc(mIn[0].getValue().value);
    v.valid = true;
    return v;
}


#endif // BLOCK_H