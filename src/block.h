// block.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef BLOCK_H
#define BLOCK_H

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "debug.h"
#include "defs.h"
#include "iblock.h"
#include "wire.h"

/**
 * @brief Input block.
 */
class Input: public IBlock
{
    public:
        /**
         * @brief Input constructor
         * @param value     Initial value of constructor.
         */
        Input(long id, Value value):
            IBlock(id), mO(value.type)
        {
            Debug::Block("Input::Input");
            setValue(value);
        }

        /**
         * @brief Assigns wire to the port.
         * @param w         Wire to assign.
         * @param key       Key of the wire.
         * @param port      Port to assign to.
         */
        void addWire(Wire* w, long key, int port = 0) override
        {
            Debug::Block("Input::addWire()");
            if(mO.wire == nullptr) mO.wire = w;
            else throw MyError("Input has only output port", ErrorType::BlockError);
            IBlock::addWire(w, key, port);
        }

        void removeWireKey(long key)
        {
            Debug::Block("Input::removeWireKey()");
            if(mO.wire != nullptr) mO.wire = nullptr;
            IBlock::removeWireKey(key);
        }

        int getLevel() const override { return 0; }
        inline void setLevel(int) override { throw MyError("Level of the input is constant", ErrorType::BlockError); }

        bool isInput() override { return true; }

        SimulationResults distributeResult() override
        {
            Debug::Block("Input::distributeResult()");
            SimulationResults sr;
            Result r;
            Value v = getValue();

            r.value = v.value;
            r.type = v.type;
            r.level = 0;

            sr.insertBlock(getId(), r);
            return mO.distributeResult(sr);
        }

    private:
        Port mO; /**< Output wire. */
};

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
            for(auto& it: intypes) { mIn.push_back(std::make_shared<Port>(it)); }
            for(auto& it: outtypes) { mOut.push_back(std::make_shared<Port>(it)); }
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

        SimulationResults& distributeResult(SimulationResults& sr) override 
        {
            Debug::Block("Block::distributeResult()");
            for(auto& it: mIn) { if(!it->getValue().valid) { return sr; } }

            Result r;
            Compute();
            Value v = getValue();

            r.value = v.value;
            r.type = v.type;
            r.level = 0;

            sr.insertBlock(getId(),r);

            SimulationResults tmp;
            for(auto& it: mOut) { tmp.mergeWith(it->distributeResult(sr)); }
            sr.mergeWith(tmp);
            return sr;
        }

    private:
        T mfunc; /**< Represents the functionality. */

        std::vector<std::shared_ptr<Port>> mIn;
        std::vector<std::shared_ptr<Port>> mOut;

        void CheckTypes(std::vector<std::shared_ptr<Port>>&);

        /**
         * @brief Compute the result.
         */
        void Compute();
        Value Compute(T) { throw MyError("Not implemented computation.", ErrorType::MathError); }

};

template <class T>
void Block<T>::removeWireKey(long id)
{
    Debug::Block("Block::removeWireKey("+std::to_string(id)+")"); 
    if(getWireKeys().count(id) == 0) return;
    if(getWireKeys().at(id) < 0) mOut.at(-getWireKeys().at(id)-1)->disconnect();
    else mIn.at(getWireKeys().at(id))->disconnect();

    IBlock::removeWireKey(id);
}

template <class T>
void Block<T>::addWire(Wire *w, long key, int port)
{
    Debug::Block("Block::addWire");
    std::vector<std::shared_ptr<Port>>& v = (port < 0)?mOut:mIn;
    int index = (port < 0) ? (-port-1):(port);

    // connect wire
    if(v[index]->wire == nullptr) v[index]->wire = w;
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
    if(port < 0 && getLevel() >= 0)
    {
        for(auto& it: v)
        {
            std::set<int> prop;
            prop.insert(getId());
            it->propagateLevel(getLevel(), prop);
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
    for(auto& it: mOut) { it->propagateLevel(level, prop); }
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
    v.type = mOut.at(0)->type;
    v.value = mfunc(mIn.at(0)->getValue().value, mIn.at(1)->getValue().value);
    v.valid = true;
    return v;
}

template<>
Value Block<std::function<double(double)>>::Compute(std::function<double(double)>)
{
    Value v;
    v.type = mOut.at(0)->type;
    v.value = mfunc(mIn.at(0)->getValue().value);
    v.valid = true;
    return v;
}

template <class T>
void Block<T>::CheckTypes(std::vector<std::shared_ptr<Port>>&)
{
    // add type check
}

#endif // BLOCK_H
