// model.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>

#include <QObject>

#include "config.h"
#include "defs.h"
#include "iblock.h"
#include "wire.h"

/**
 * @brief Saved state of the model.
 */
struct ModelState {
    std::map<long,long> blocks; /**< Block state <id,type>. */
    // wires
};

/**
 * @brief Model.
 */
class Model: public QObject
{
    Q_OBJECT

    public:
        /**
         * @brief   Model destructor.
         */
        ~Model() { slotReset(); }

        /**
         * @brief   Computes the results.
         * @returns Results of connected blocks.
         */
        SimulationResults startComputation();
        /**
         * @brief Gets the state (for saving).
         * @returns The state to save.
         */
        ModelState getState();
        /**
         * @brief Sets the state (loading the file).
         * @param state     State to set.
         */
        void setState(ModelState);
        /**
         * @brief Resets the model.
         */
        void reinit() { slotReset(); }

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
        void slotCreateWire(PortID startkey, PortID endkey, long& key, bool& success);
        /**
         * @brief Invocated, when wire is deleted (in GUI).
         * @param key       Key of deleted wire.
         */
        void slotDeleteWire(long key);
        /**
         * @brief Invocated, when input is created (in GUI).
         * @param value     Value, assigned to the input.
         * @param key       Reference to return generated key.
         */
        void slotCreateInput(Value, long& key);
        /**
         * @brief Invocated, when input value is changed (in GUI).
         * @param key       Key of input, whose value changed.
         * @param value     New value.
         */
        void slotInputValueChanged(long key, Value);
        /**
         * @brief Resets the model.
         */
        void slotReset();

    signals:
        /**
         * @brief Emitted to the wire, connected to the block being deleted.
         * @param key       Key of the connected wire.
         */
        void sigDeleteWire(long key);

    private:
        std::map<long, std::shared_ptr<IBlock>> mBlocks; /**< Map of blocks. */
        std::set<long> mInputs; /**< Input blocks set. */
        std::map<long, std::shared_ptr<Wire>> mWires;    /**< Map of wires. */

        /**
         * @brief   Resets the model after the computation.
         */
        void endComputation();

        int mblockkey = 0; /**< Key generator for the blocks. */
        int mwirekey = 0; /**< Key generator for the wires. */
        /**
         * @brief Generator of the block key.
         * @returns         The generated key
         */
        long GenerateBlockKey() { return mblockkey++; }
        /**
         * @brief Generator of the wire key.
         * @returns         The generated key.
         */
        long GenerateWireKey() { return mwirekey++; }

};

#endif // MODEL_H
