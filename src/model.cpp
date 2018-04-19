
#include <iostream>

#include "block.h"
#include "config.h"
#include "model.h"

Model::~Model()
{
    //for(auto& it: mWires) delete it.second;
    //for(auto& it: mBlocks) delete it.second;
}

void Model::slotCreateBlock(long& key)
{
    key = GenerateBlockKey(key);
    //std::string gtype = Config::getGType();

    std::shared_ptr<IBlock> b;

    std::cerr << "Give me " << key << ", so " << (key&0xFF) << "\n"; 
    switch(type)
    {
        // two inputs, one output
        case BlockType::TwoIn_OneOut:
            try {
                b = std::make_shared<IBlock>(
                    Block<std::function<double(double,double)>> (
                        Config::getFunc_2I1O(key & 0xFF),
                        Config::getInput(type),
                        Config::getOutput(type))
                );
            } catch(MyError e) { std::cerr << e.getMessage() << "\n"; throw e; }
            
            break;
        
        // one input, one output
        case BlockType::OneIn_OneOut:
            try {
                b = std::make_shared<IBlock>(
                    Block<std::function<double(double)>> (
                        Config::getFunc_1I1O(key & 0xFF),
                        Config::getInput(type),
                        Config::getOutput(type))
                );
            } catch(MyError e) { std::cerr << e.getMessage() << "\n"; throw e; }
            break;

        // unknown block   
        default:
            throw MyError("Unknown block type", ErrorType::BlockError);
    }
    mBlocks.insert( std::make_pair(key, b) );
    std::cerr << "model: " << key << "\n";
}

void Model::slotDeleteBlock(long key)
{
    // get connected wires
    std::set<long> wkeys = mBlocks.at(key)->getWireKeys();

    // erase connected wires
    for(auto& it: wkeys)
    {
        //delete mWires.at(it);
        mWires.erase(it);
        emit sigDeleteWire(it);
    }
    
    // erase the block
    //delete mBlocks.at(key);
    mBlocks.erase(key);
}

void Model::slotCreateWire(PortID startkey, PortID endkey, long& key)
{
    key = GenerateWireKey(key);
    std::shared_ptr<Wire> w = std::make_shared<Wire>(
        Wire(key, *mBlocks.at(startkey.key), startkey.port,
                  *mBlocks.at(endkey.key), endkey.port)
    );
    
    mWires.insert( std::make_pair(key, w) );
}

void Model::slotDeleteWire(long key)
{
    //delete mWires.at(key);
    mWires.erase(key);
}