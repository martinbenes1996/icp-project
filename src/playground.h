#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <map>
#include <memory>
#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPaintEvent>
#include <QVBoxLayout>

#include "config.h"
#include "defs.h"
#include "guiblock.h"

class PlayGround: public QWidget
{
    Q_OBJECT
    public:
        PlayGround(QWidget* parent = 0);

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void paintEvent(QPaintEvent*);

    public slots:
        /**
         * @brief   Slot for menu's signal, that choice was set/unset.
         * @param choice    New choice status.
         */
        void slotChoiceMode(bool choice) { mchoice = choice; }
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
        void sigCreateBlock(BlockType type, long& key);
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
        void sigCreateWire(PortID startkey, PortID endkey, long& id);
        /**
         * @brief   Graphic's signal to the model, that wire is deleted.
         * @param key       Key of deleted wire.
         */
        void sigDeleteWire(long key);

    private:
        bool mchoice = false; /**< Weather the block is being placed. */

        std::map<long, std::shared_ptr<GuiBlock>> mBlocks; /**< Placed blocks. */

        // i tried something. read something about these
        QGraphicsView *mview = nullptr;
        QGraphicsScene *mscene = nullptr;

        

};

#endif // PLAYGROUND_H
