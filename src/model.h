#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>

#include <QObject>

#include "iblock.h"
#include "wire.h"

class Model: public QObject
{
    Q_OBJECT
    
    public slots:
        void slotCreateBlock(long type, long& key);
        void slotDeleteBlock(long key);
        void slotCreateWire(long startkey, long endkey, long& id);
        void slotDeleteWire(long key);
    
    signals:
        void sigDeleteWire(long key);

    private:
        std::map<long, IBlock*> mBlocks; /**< Map of blocks. */
        std::map<long, Wire*> mWires;    /**< Map of wires. */

        long GenerateBlockKey() { return mblock_key++; }
        long GenerateWireKey() { return mwire_key++; }
        long mblock_key = 0;
        long mwire_key = 0;

};

#endif // MODEL_H