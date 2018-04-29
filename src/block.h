#ifndef BLOCK_H
#define BLOCK_H

#include <functional>
#include <set>
#include <string>
#include <vector>

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
         * @param func      Functionality of the block (lambdas as templates).
         * @param intypes   Types of inputs.
         * @param outtypes  Types of input.
         * @param type_o    Type of the output.
         */
        Block(long id, T func, std::vector<std::string> intypes, std::vector<std::string> outtypes, long type):
            IBlock(id, type), mfunc(func)
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
        inline void addWire(Wire *, long, int port = 0) override;

        /**
         * @brief Propagates level towards.
         * @param level     Propagated level.
         */
        inline void propagateLevel(int, std::set<int>) override;

        inline void removeWireKey(long) override;
    
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
void Block<T>::removeWireKey(long id)
{
    if(getWireKeys().at(id) < 0) mOut[id].disconnect();
    else mIn[id].disconnect();

    IBlock::removeWireKey(id);
}

template <class T>
void Block<T>::addWire(Wire *w, long key, int port)
{
    Debug::Block("Block::addWire");
    std::vector<Port>& v = (port < 0)?mOut:mIn;
    int index = (port < 0) ? (-port-1):(port);
    
    // connect wire
    if(v[index].wire == nullptr) v[index].wire = w;
    // already connected port
    else throw MyError("Adding wire to connected port", ErrorType::WireError);
    
    // add to keys
    IBlock::addWire(w, key, port);

      // input     // level is less than propagated
    if(isInputPort(port) && getLevel() < w->getLevel()) 
    { 
        setLevel( w->getLevel() ); 
    }
    

    // output
    if(port < 0)
    {
        for(auto& it: v)
        {
            std::set<int> prop;
            prop.insert(getId());
            it.propagateLevel(getLevel(), prop);
        }
    }

    
}


template <class T>
void Block<T>::propagateLevel(int level, std::set<int> prop)
{
    Debug::Block("Block::propagateLevel");
    // cycle detection
    if( prop.count(getId()) > 0)
        throw MyError("Cycle detected!", ErrorType::BlockError); 
    
    // level setter
    if(level > getLevel()) { setLevel(level); }

    // propagate
    prop.insert(getId());
    for(auto& it: mOut) { it.propagateLevel(level, prop); }
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