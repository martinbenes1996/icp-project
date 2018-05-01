// playground.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


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

class PlayGround: public QWidget
{
    Q_OBJECT
    public:

        PlayGround(QWidget* parent = 0);

        /**
         * @brief   Getter for play ground view.
         * @returns pointer to playGroundView
         */
	    PlayGroundView *getPlayGroundView() { return mview; }
	    /**
         * @brief   Button is clicked in menu.
         * @returns true -> choice made, false -> choice not made
         */
        bool hasChoice() { return mchoice != -1; }

        void reinit();
        std::map<long,GuiBlockDescriptor> getBlockState();
        void setBlockState(std::map<long,GuiBlockDescriptor>);

        void inputClick(int);

        /**
         * @brief   Sets new value of a wire for display.
         * @param   id          ID of the wire
         * @param   newValue    new value
         */
        void setWireValue(long id, double newValue);

        // slots and signals will have to be reworked
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
         * @brief   Gets ID from block pointer.
         * @param   block   pointer to a block
         * @returns ID of the block
         */
        long getIDFromBlock(std::shared_ptr<GuiBlock> block);
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
        void annulateChoice() { mchoice = -1; mwire = minput = false; }

        std::map<long, std::shared_ptr<GuiBlock>> mBlocks; /**< Placed blocks. */
        std::map<long, std::shared_ptr<MyWire>> mWires; /**< Placed wires. */
        std::map<long, std::shared_ptr<GuiInput>> mInputs; /**< Placed inputs. */

        QSignalMapper mmapper;

        QVBoxLayout *layout = nullptr;

        PlayGroundView *mview = nullptr;
        QGraphicsScene *mscene = nullptr;

        //QPointF drawLinePoint = QPointF();
        bool createWire = false;    /**< True when two points are selected -> create wire. */
        int connector1;             /**< Connector of the first block. */
        int connector2;             /**< Connector of the second block. */
        std::shared_ptr<GuiBlock> block1 = nullptr; /**< First block. */
        std::shared_ptr<GuiBlock> block2 = nullptr; /**< Second block. */

};

// class for displaying playground and processing mouse interactions
class PlayGroundView: public QGraphicsView
{
    Q_OBJECT

    // borrowed constructor -> this class only overrides some methods and sends signals
    using QGraphicsView::QGraphicsView;

    public:

        //void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event/*, PlayGround *par*/);
        //void mouseReleaseEvent(QMouseEvent *event);
        //void paintEvent(QPaintEvent*);

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
