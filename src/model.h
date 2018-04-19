#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <memory>
#include <string>

#include <QObject>

#include "config.h"
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
        std::map<long, std::shared_ptr<IBlock>> mBlocks; /**< Map of blocks. */
        std::map<long, std::shared_ptr<Wire>> mWires;    /**< Map of wires. */

        /**
         * @brief Generator of the block key.
         * @returns         The generated key
         */
        long GenerateBlockKey(long key) 
        { 
            static long gkey = 0;
            return ((gkey++) << 16) | (key & 0xFFFF);
        }
        /**
         * @brief Generator of the wire key.
         * @returns         The generated key.
         */
        long GenerateWireKey(long key) 
        { 
            static long gkey = 0;
            return ((gkey++) << 16) | (key & 0xFFFF);
        }


};

#endif // MODEL_H