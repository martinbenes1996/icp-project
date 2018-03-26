
#include "block.h"
#include "config.h"
#include "model.h"

void Model::slotCreateBlock(long type, long& key)
{
    key = GenerateBlockKey();

    if( type & B_2I1O )
    {
        std::string gtype = Config::getGType();
        IBlock * b = new Block_2I1O( Config::get2I1OFunction( unmask(type) ), gtype, gtype, gtype );
        mBlocks.insert( std::make_pair(key, b) );
    }
    else if( type & B_1I1O )
    {
        std::string gtype = Config::getGType();
        IBlock * b = new Block_1I1O( Config::get1I1OFunction( unmask(type) ), gtype, gtype );
        mBlocks.insert( std::make_pair(key, b) );
    }
    else throw MyError("Unknown block type", ErrorType::BlockError);

}

void Model::slotDeleteBlock(long key)
{
    (void)key;
}

void Model::slotCreateWire(long startkey, long endkey, long& id)
{
    (void)startkey;
    (void)endkey;
    (void)id;
}

void Model::slotDeleteWire(long key)
{
    (void)key;
}