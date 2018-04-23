
#include <iostream>

#include "block.h"
#include "config.h"
#include "model.h"

Model::~Model()
{
    //for(auto& it: mWires) delete it.second;
    //for(auto& it: mBlocks) delete it.second;
}

void Model::slotCreateBlock(long type, long& key)
{
    key = GenerateBlockKey();
    Debug::Model( "Create block "+std::to_string(key) );

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
                Config::getOutput(type)
            );
            break;

        // one input, one output
        case BlockType::OneIn_OneOut:
            b = std::make_shared< Block<std::function<double(double)>> >(
                key,
                Config::getFunc_1I1O(type),
                Config::getInput(type),
                Config::getOutput(type)
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
    Debug::Model( "Delete block "+std::to_string(key) );
    // get connected wires
    std::map<long,int> wkeys = mBlocks.at(key)->getWireKeys();

    // erase connected wires
    for(auto& it: wkeys) { emit sigDeleteWire(it.first); }

    // erase the block
    mBlocks.erase(key);
}
// nejak zarid, at se success nastavi na false, pokud se to nepovede. Nechci ti pokazit ten tvuj sablonovy skvost.
void Model::slotCreateWire(PortID startkey, PortID endkey, long& key, bool& success)
{
    key = GenerateWireKey();
    Debug::Model( "Create wire "+std::to_string(key) );

    std::shared_ptr<Wire> w = std::make_shared<Wire>(
        key,*mBlocks.at(startkey.key), startkey.port,
            *mBlocks.at(endkey.key), endkey.port
    );


    mWires.insert( std::make_pair(key, w) );

    //mBlocks.at(endkey.key)->addWire(w.get(), key, endkey.port);
    //mBlocks.at(startkey.key)->addWire(w.get(), key, startkey.port);

}

void Model::slotDeleteWire(long key)
{
    Debug::Model( "Delete wire "+std::to_string(key) );
    mWires.erase(key);
}
