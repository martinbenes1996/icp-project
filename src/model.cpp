/**
 * @file model.cpp
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief model module
 *
 * This module contains model implementation.
 */

#include <iostream>

#include "block.h"
#include "config.h"
#include "model.h"

void Model::slotCreateBlock(long type, long& key)
{
    key = GenerateBlockKey();
    Debug::Model( "Model::slotCreateBlock("+std::to_string(key)+")" );

    std::shared_ptr<IBlock> b;
    BlockType bt = Config::decodeBlockType(type);

    switch(bt)
    {
        // two inputs, one output
        case BlockType::TwoIn_OneOut:
            b = std::make_shared< Block<std::function<double(double,double)>> >(
                key,
                Config::getFunc_2I1O(type),
                Config::getInput(type),
                Config::getOutput(type),
                type
            );
            break;

        // one input, one output
        case BlockType::OneIn_OneOut:
            b = std::make_shared< Block<std::function<double(double)>> >(
                key,
                Config::getFunc_1I1O(type),
                Config::getInput(type),
                Config::getOutput(type),
                type
            );
            break;

        // unknown block
        default:
            throw MyError("Unknown block type", ErrorType::BlockError);
    }
    mBlocks.insert( std::make_pair(key, b) );
}

void Model::slotDeleteBlock(long key)
{
    Debug::Model( "Model::slotDeleteBlock("+std::to_string(key)+")" );
    // get connected wires
    std::map<long,int> wkeys = mBlocks.at(key)->getWireKeys();

    // erase connected wires
    for(auto& it: wkeys)
    {
        slotDeleteWire(it.first);
        emit sigDeleteWire(it.first);
    }

    // erase the block
    if(mInputs.count(key) > 0) mInputs.erase(key);
    mBlocks.erase(key);

}

void Model::slotCreateWire(PortID startkey, PortID endkey, long& key, bool& success)
{
    if(startkey.port >= 0 && endkey.port < 0)
    {
        PortID tmp;
        tmp = startkey;
        startkey = endkey;
        endkey = tmp;
    }
    if(startkey.port >= 0 && endkey.port >= 0)
    {
        //std::cerr << "Must be output to input!\n";
        success = false;
        return;
    }

    key = GenerateWireKey();
    Debug::Model( "Model::slotCreateWire("+std::to_string(key)+")" );

    if(mBlocks.count(startkey.key) == 0 || mBlocks.count(endkey.key) == 0)
    {
        success = false;
        return;
    }

    std::shared_ptr<Wire> w;
    try {
        w = std::make_shared<Wire>(
        key,*mBlocks.at(startkey.key), startkey.port,
            *mBlocks.at(endkey.key), endkey.port
        );
    } catch(MyError& e) {
        //std::cerr << e.getMessage() << "\n";
        success = false;
        return;
    }

    mWires.insert( std::make_pair(key, w) );

    success = true;

}

void Model::slotDeleteWire(long key)
{
    Debug::Model("Model::slotDeleteWire("+std::to_string(key)+")");
    if(mWires.count(key) > 0)
        mWires.erase(key);
}

void Model::slotCreateInput(Value value, long& key)
{
    key = GenerateBlockKey();
    Debug::Model( "Model::slotCreateInput("+std::to_string(key)+")" );

    std::shared_ptr<IBlock> b = std::make_shared<Input>(key,value);

    mBlocks.insert( std::make_pair(key, b) );
    mInputs.insert( key );
}

void Model::slotInputValueChanged(long key, Value value)
{
    mBlocks.at(key)->setValue(value);
}

SimulationResults Model::startComputation()
{
    // collect results
    SimulationResults::resetMaxLevel();
    SimulationResults sr;
    for(auto& inkey: mInputs)
    {
        sr.mergeWith(mBlocks.at(inkey)->distributeResult());
    }

    endComputation();
    return sr;
}

void Model::endComputation()
{
    for(auto& it: mBlocks)
    {
        if(!it.second->isInput())
            it.second->resetValue();
    }
}

void Model::slotReset()
{
    mWires.clear();
    mBlocks.clear();
    mInputs.clear();
    mblockkey = 0;
    mwirekey = 0;
}

ModelState Model::getState()
{
    ModelState s;
    for(auto& it: mBlocks)
    {
        s.blocks.insert( std::make_pair(it.first, it.second->getType()) );
    }
    return s;
}

void Model::setState(ModelState s)
{
    mblockkey = 0;
    Debug::File("Model::setState()");
    for(auto& it: s.blocks)
    {

        mblockkey = it.first;
        long key;

        // input
        if(it.second == -1)
        {
            slotCreateInput(Value(), key);
        }
        // blcok
        else
        {
            slotCreateBlock(it.second, key);
        }
        Debug::File("Save "+std::to_string(it.second)+" as "+std::to_string(it.first));

    }
    // wires
}


