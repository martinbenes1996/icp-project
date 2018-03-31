#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>

#include <QObject>

#include "iblock.h"
#include "wire.h"

/**
 * @brief Model.
 */
class Model: public QObject
{
    Q_OBJECT

    public:
        ~Model();
    
    public slots:
        /**
         * @brief Invocated, when block is created (in GUI).
         * @param type      Type, first octet includes type.
         * @param key       Reference to return generated key.
         */
        void slotCreateBlock(long type, long& key);
        /**
         * @brief Invocated, when block is deleted (in GUI).
         * @param key       Key of deleted block.
         */
        void slotDeleteBlock(long key);
        /**
         * @brief Invocated, when wire is created (in GUI).
         * @param startkey  Key of the start block.
         * @param endkey    Key of the end block.
         * @param key       Reference to return generated key.
         */ 
        void slotCreateWire(PortID startkey, PortID endkey, long& key);
        /**
         * @brief Invocated, when wire is deleted (in GUI).
         * @param key       Key of deleted wire.
         */
        void slotDeleteWire(long key);
    
    signals:
        /**
         * @brief Emitted to the wire, connected to the block being deleted.
         * @param key       Key of the connected wire.
         */
        void sigDeleteWire(long key);

    private:
        std::map<long, IBlock*> mBlocks; /**< Map of blocks. */
        std::map<long, Wire*> mWires;    /**< Map of wires. */

        /**
         * @brief Generator of the block key.
         * @returns         The generated key
         */
        long GenerateBlockKey() 
        { 
            static long key = 0;
            return key++; }
        /**
         * @brief Generator of the wire key.
         * @returns         The generated key.
         */
        long GenerateWireKey() 
        { 
            static long key = 0;
            return key++;
        }

};

#endif // MODEL_H