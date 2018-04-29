// model.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>

#include "block.h"
#include "config.h"
#include "model.h"

Model::~Model()
{
    slotReset();
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
        std::cerr << "deleting " << it.first << "\n";
        slotDeleteWire(it.first);
        emit sigDeleteWire(it.first);
    }

    // erase the block
    mBlocks.erase(key);
    
}
// nejak zarid, at se success nastavi na false, pokud se to nepovede. Nechci ti pokazit ten tvuj sablonovy skvost.
void Model::slotCreateWire(PortID startkey, PortID endkey, long& key, bool& success)
{
    if((startkey.port < 0 && endkey.port < 0)
    || (startkey.port >= 0 && endkey.port >= 0))
    {
        std::cerr << "Must be output to input!\n";
        success = false;
        return;
    }

    key = GenerateWireKey();
    Debug::Model( "Model::slotCreateWire "+std::to_string(key) );

    std::shared_ptr<Wire> w;
    try {
        w = std::make_shared<Wire>(
        key,*mBlocks.at(startkey.key), startkey.port,
            *mBlocks.at(endkey.key), endkey.port
        );
    } catch(MyError& e) { 
        std::cerr << e.getMessage() << "\n";
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

void Model::startComputation()
{
    blockComputeQueue = std::queue<long>();
    int level = 0;
    bool end = false;
    while(!end)
    {
        bool found = false;
        for(auto& it: mBlocks) {
            if(it.second->getLevel() == level) {
                blockComputeQueue.push(it.first);
                found = true;
            }
            if(it.second->getLevel() == -1)
            {
                throw MyError("Not all blocks connected!", ErrorType::BlockError);
            }
        }

        level++;
        end = !found;
    }
}

Computation Model::computeBlock()
{
    // get id
    long id = blockComputeQueue.front();
    blockComputeQueue.pop();

    // compute
    Computation c;
    c.key = id;
    c.result = mBlocks.at(id)->getValue();
    return c;
}

void Model::slotReset()
{
    mBlocks.clear();
    mWires.clear();
    blockComputeQueue = std::queue<long>();
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
    for(auto& it: s.blocks)
    {
        mblockkey = it.first;
        long key;
        slotCreateBlock(it.second, key);
    }
    // wires
}
