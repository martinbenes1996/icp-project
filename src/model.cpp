
#include <iostream>

#include "block.h"
#include "config.h"
#include "model.h"

Model::~Model()
{
    for(auto& it: mWires) delete it.second;
    for(auto& it: mBlocks) delete it.second;
}

void Model::slotCreateBlock(long type, long& key)
{
    key = GenerateBlockKey();
    std::string gtype = Config::getGType();

    IBlock * b;
    switch( Config::getBlockType(type) )
    {
        // two inputs, one output
        case BlockType::TwoIn_OneOut:
            b = new Block<std::function<double(double,double)>> (
                    Config::getFunc_2I1O(type),
                    Config::getInput(type),
                    Config::getOutput(type));
            break;
        
        // one input, one output
        case BlockType::OneIn_OneOut:
            b = new Block<std::function<double(double)>> (
                    Config::getFunc_1I1O(type),
                    Config::getInput(type),
                    Config::getOutput(type));
            break;

        // unknown block   
        default:
            throw MyError("Unknown block type", ErrorType::BlockError);
    }
    mBlocks.insert( std::make_pair(key, b) );
}

void Model::slotDeleteBlock(long key)
{
    // get connected wires
    std::set<long> wkeys = mBlocks.at(key)->getWireKeys();

    // erase connected wires
    for(auto& it: wkeys)
    {
        delete mWires.at(it);
        mWires.erase(it);
        emit sigDeleteWire(it);
    }
    
    // erase the block
    delete mBlocks.at(key);
    mBlocks.erase(key);
}

void Model::slotCreateWire(PortID startkey, PortID endkey, long& key)
{
    key = GenerateWireKey();
    Wire* w = new Wire(key, *mBlocks.at(startkey.key), startkey.port,
                            *mBlocks.at(endkey.key), endkey.port);
    
    mWires.insert( std::make_pair(key, w) );
}

void Model::slotDeleteWire(long key)
{
    delete mWires.at(key);
    mWires.erase(key);
}