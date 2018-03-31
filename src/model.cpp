
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

    if( type & B_2I1O )
    {
        std::string gtype = Config::getGType();
        IBlock * b = new Block_2I1O( Config::get2I1OFunction(unmask(type)),
                                        gtype, gtype, gtype );
        mBlocks.insert( std::make_pair(key, b) );
    }
    else if( type & B_1I1O )
    {
        std::string gtype = Config::getGType();
        IBlock * b = new Block_1I1O( Config::get1I1OFunction(unmask(type)),
                                        gtype, gtype );
        mBlocks.insert( std::make_pair(key, b) );
    }
    else throw MyError("Unknown block type", ErrorType::BlockError);

}

void Model::slotDeleteBlock(long key)
{
    // get connected wires
    std::vector<long> wkeys = mBlocks.at(key)->getWireKeys();

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
    Wire* w = new Wire(*mBlocks.at(startkey.key), startkey.port,
                       *mBlocks.at(endkey.key), endkey.port);
    
    mWires.insert( std::make_pair(key, w) );
}

void Model::slotDeleteWire(long key)
{
    delete mWires.at(key);
    mWires.erase(key);
}