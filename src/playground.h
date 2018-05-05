
/**
 * @file playground.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief draw place interface
 *
 * This module contains playground definition.
 */

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QSignalMapper>        // map block signals
#include <QList>

#include "config.h"
#include "defs.h"
#include "guiblock.h"

class PlayGroundView;

/**
 * @brief PlayGround class.
 */
class PlayGround: public QWidget
{
    Q_OBJECT
    public:
        /**
         * @brief PlayGround constructor.
         * @param parent        Parent.
         */
        PlayGround(QWidget* parent = 0);

        /**
         * @brief   Getter for play ground view.
         * @returns pointer to playGroundView
         */
	    PlayGroundView *getPlayGroundView() { return mview; }
	    /**
         * @brief   Getter for play ground scene.
         * @returns pointer to QGraphicsScene
         */
	    QGraphicsScene *getPlayGroundScene() { return mscene; }
	    /**
         * @brief   Button is clicked in menu.
         * @returns true -> choice made, false -> choice not made
         */
        bool hasChoice() { return mchoice != -1; }

        /**
         * @brief Reinitializes the playground.
         */
        void reinit();

        /**
         * @brief Returns block states (for saving).
         * @returns Block states.
         */
        std::map<long,GuiBlockDescriptor> getBlockState();
        /**
         * @brief Returns wire states (for saving).
         * @returns Wire states.
         */
        std::vector<struct wireState> getWireState();
        /**
         * @brief Sets block states (for loading).
         * @param m         Block states.
         */
        void setBlockState(std::map<long,GuiBlockDescriptor>);
        /**
         * @brief Sets wire states (for loading).
         * @param m         Wire states.
         */
        void setWireState(std::vector<struct wireState> v);

        /**
         * @brief   Gets ID from block pointer.
         * @param   block   pointer to a block
         * @returns ID of the block
         */
        long getIDFromBlock(std::shared_ptr<GuiBlock> block);
        /**
         * @brief   Gets ID from input pointer.
         * @param   block   pointer to a input
         * @returns ID of the input
         */
        long getIDFromInput(std::shared_ptr<GuiInput> block);
        /**
         * @brief Input clicked.
         * @param id    Id of the input.
         */
        void inputClick(int);

        /**
         * @brief   Sets new value of a wire for display.
         * @param   id          ID of the wire
         * @param   newValue    new value
         */
        void setWireValue(long id, Value v);
        /**
         * @brief   Sets new value of a block for display.
         * @param   id          ID of the block
         * @param   newValue    new value
         */
        void setBlockValue(long id, Value v);
        /**
         * @brief   Sets new color of a wire for display.
         * @param   id          ID of the wire
         * @param   active      true -> red, false -> black
         */
        void setWireColor(long id, bool active);
        /**
         * @brief   Sets new color of a block for display.
         * @param   id          ID of the block
         * @param   active      true -> red picture, false -> normal picture
         */
        void setBlockColor(long id, bool active);
        /**
         * @brief   Sets default color of all entities in scene.
         */
        void setAllDefaultColor();
        /**
         * @brief Clears all the values and the colors.
         */
        void clearComputation();
        /**
         * @brief   Computing bit setter.
         * @param v         True if computing.
         */
        void setComputing(bool v) { mcompute = v; }

    public slots:
        /**
         * @brief   Slot for menu's signal, that choice was set/unset.
         * @param   choice    New choice status.
         */
        void slotTypeChoice(long choice) { annulateChoice(); mchoice = choice; }
        /**
         * @brief   Slot for menu's signal, that wire was chosen.
         */
        void slotWireMode() { annulateChoice(); mwire = true; }    // wire choice
        /**
         * @brief   Slot for menu's signal, that input was chosen.
         */
        void slotInput() { annulateChoice(); minput = true; }

        /**
         * @brief   Slot for PlayGroundView's signal, left mouse press.
         */
        void slotViewLeftClick(QMouseEvent *event);

        /**
         * @brief   Slot for PlayGroundView's signal, right mouse press.
         */
        void slotViewRightClick(QMouseEvent *event);

        /**
         * @brief   Slot for Blocks's signal, mouse press.
         */
        void slotBlockClick(int);
        /**
         * @brief   Slot for Wire's signal, mouse press.
         */
        void slotForkWire(long, QPointF);
        /**
         * @brief   Slot for signal, that wire should be deleted.
         * @param   index    Index of a wire.
         */
        void slotDeleteWire(long);
        /**
         * @brief   Slot for signal, that value changed.
         */
        void slotValueChanged();

    signals:
        /**
         * @brief   Signal (to the menu), that choice is rejected.
         */
        void sigChoiceRejected();

        /**
         * @brief   Graphic's signal to the model, that block has been created.
         *          The generated id (in the model) is passed by key.
         * @param type      Type of created block.
         * @param key       Reference for passing a key (backwards).
         */
        void sigCreateBlock(long type, long& key);
        /**
         * @brief   Graphic's signal to the model, that input has been created.
         *          The generated id (in the model) is passed by key.
         * @param value     Assigned value.
         * @param key       Reference for passing a key (backwards).
         */
        void sigCreateInput(Value value, long& key);
        /**
         * @brief   Graphic's signal to the model, that input changed its value.
         * @param key       Key of input.
         * @param value     New value.
         */
        void sigInputValueChanged(long key, Value value);
        /**
         * @brief   Graphic's signal to the model, that block is deleted.
         * @param key       Key of deleted block.
         */
        void sigDeleteBlock(long key);
        /**
         * @brief   Graphic's signal to the model, that wire has been created.
         *          The generated id (in the model) is passed by key.
         * @param startkey  Start key (port id).
         * @param endkey    End key (port id)
         * @param key       Reference for passing a key (backwards).
         */
        void sigCreateWire(PortID startkey, PortID endkey, long& id, bool& success);
        /**
         * @brief   Graphic's signal to the model, that wire is deleted.
         * @param key       Key of deleted wire.
         */
        void sigDeleteWire(long key);

    private:
        /**
         * @brief   Creates a wire.
         * @returns true -> success, false -> failure
         */
        bool createWireFunction();
        /**
         * @brief   Deletes a wire.
         * @param   i   index of the block
         */
        void deleteWireFunction(long i);

        long mchoice = -1;  /**< Weather the block is being placed. */
        bool mwire = false; /**< Weather the wire is being placed. */
        bool minput = false; /**< Weather the input is being placed. */
        bool mcompute = false; /**< Weather computing. */
        void annulateChoice() { mchoice = -1; mwire = minput = false; }

        std::map<long, std::shared_ptr<GuiBlock>> mBlocks; /**< Placed blocks. */
        std::map<long, std::shared_ptr<MyWire>> mWires; /**< Placed wires. */
        std::map<long, std::shared_ptr<GuiInput>> mInputs; /**< Placed inputs. */

        QSignalMapper mmapper;  /**< Signal mapper for the blocks. */
        QVBoxLayout *layout = nullptr; /**< Layout. */

        PlayGroundView *mview = nullptr; /**< View. */
        QGraphicsScene *mscene = nullptr; /**< Scene. */

        bool createWire = false;    /**< True when two points are selected -> create wire. */
        int connector1;             /**< Connector of the first block. */
        int connector2;             /**< Connector of the second block. */
        std::shared_ptr<GuiInput> iblock1 = nullptr; /**< First input. */
        std::shared_ptr<GuiBlock> block1 = nullptr; /**< First block. */
        std::shared_ptr<GuiInput> iblock2 = nullptr; /**< Second input. */
        std::shared_ptr<GuiBlock> block2 = nullptr; /**< Second block. */

};

/**
 * @brief PlayGroundView class. For displaying playground and processing mouse interactions.
 */
class PlayGroundView: public QGraphicsView
{
    Q_OBJECT

    /**
     * @brief Borrowed constructor.
     */
    using QGraphicsView::QGraphicsView;

    public:
        /**
         * @brief   Mouse press handler.
         * @param event     Description of event.
         */  
        void mousePressEvent(QMouseEvent *event);

    signals:
        /**
         * @brief   Signal to the PlayGround, left click.
         */
        void sigViewLeftClick(QMouseEvent *event);
        /**
         * @brief   Signal to the PlayGround, right click.
         */
        void sigViewRightClick(QMouseEvent *event);
    
};

#endif // PLAYGROUND_H
